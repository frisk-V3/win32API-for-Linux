use std::cell::Cell;

thread_local! {
    static LAST_ERROR: Cell<u32> = Cell::new(0);
}
