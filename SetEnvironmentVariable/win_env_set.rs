use std::env;

pub fn set_environment_variable_w(name: &[u16], value: Option<&[u16]>) -> Result<(), u32> {
    // UTF-16 → UTF-8
    let name_string = String::from_utf16(name).map_err(|_| 87u32)?; // ERROR_INVALID_PARAMETER

    if name_string.is_empty() || name_string.contains('=') {
        return Err(87); // ERROR_INVALID_PARAMETER
    }

    match value {
        None => {
            env::remove_var(&name_string);
            Ok(())
        }
        Some(v) => {
            let value_string = String::from_utf16(v).map_err(|_| 87u32)?;
            env::set_var(&name_string, value_string);
            Ok(())
        }
    }
}
