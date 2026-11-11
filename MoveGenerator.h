#pragma once

#include <coroutine>
#include <exception>

#include "Board.h"

using namespace std;

class MoveGenerator {
public:
    struct promise_type {
        Move current{};
        exception_ptr error;

        MoveGenerator get_return_object()
        {
            return MoveGenerator(coroutine_handle<promise_type>::from_promise(*this));
        }
        suspend_always initial_suspend() noexcept { return {}; }
        suspend_always final_suspend() noexcept { return {}; }
        suspend_always yield_value(Move move)
        {
            current = move;
            return {};
        }
        void return_void() {}
        void unhandled_exception() { error = current_exception(); }
    };

    explicit MoveGenerator(coroutine_handle<promise_type> h) : handle(h) {}
    MoveGenerator(const MoveGenerator&) = delete;
    MoveGenerator& operator=(const MoveGenerator&) = delete;

    ~MoveGenerator()
    {
        if (handle) {
            handle.destroy();
        }
    }

    bool next()
    {
        if (handle.done()) {
            return false;
        }
        handle.resume();
        if (handle.promise().error) {
            rethrow_exception(handle.promise().error);
        }
        return !handle.done();
    }

    Move value() const { return handle.promise().current; }

private:
    coroutine_handle<promise_type> handle;
};
