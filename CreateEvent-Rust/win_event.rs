use std::sync::{Mutex, Condvar};
use std::time::{Duration, Instant};

pub struct WinEvent {
    manual_reset: bool,
    state: Mutex<bool>,
    cv: Condvar,
}

impl WinEvent {
    pub fn new(manual_reset: bool, initial_state: bool) -> Self {
        Self {
            manual_reset,
            state: Mutex::new(initial_state),
            cv: Condvar::new(),
        }
    }

    pub fn set(&self) {
        let mut state = self.state.lock().unwrap();
        *state = true;

        if self.manual_reset {
            self.cv.notify_all();
        } else {
            self.cv.notify_one();
        }
    }

    pub fn reset(&self) {
        let mut state = self.state.lock().unwrap();
        *state = false;
    }

    pub fn wait(&self, timeout_ms: u32) -> bool {
        let mut state = self.state.lock().unwrap();

        if !*state {
            if timeout_ms == u32::MAX {
                state = self.cv.wait(state).unwrap();
            } else {
                let timeout = Duration::from_millis(timeout_ms as u64);
                let (s, result) = self.cv.wait_timeout(state, timeout).unwrap();
                state = s;

                if result.timed_out() {
                    return false;
                }
            }
        }

        // auto reset
        if !self.manual_reset {
            *state = false;
        }

        true
    }
}
