## 1.1.1

### Bugfixes:
- Fixed issue causing `esp_delta_ota_patch_gen.py` to be non-functional on Windows OS.
- Replaced earlier use of subprocess commands with direct `esptool` module import based method for handling ESP chip-specific operations across all platforms.
- Replaced earlier use of subprocess commands with direct `detools` module import based method for creating and applying patches.

## 1.1.0

### Enhancements:
- Added support to pass user data to write callback with new callback function: `merged_stream_write_cb_with_user_ctx_t`
- The older write callback function: `merged_stream_write_cb_t` has been deprecated and will be removed in the next major release.
