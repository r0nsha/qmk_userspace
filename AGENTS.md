# QMK Userspace — holykeebs / r0nsha

Corne (`crkbd/rev1`) split keyboard userspace, multi-pointing-device focus (trackball + trackpoint + Cirque/Azoteq touchpads). Shared code in `users/holykeebs/`, keymap in `keyboards/crkbd/rev1/keymaps/r0nsha/`.

## Build & flash

```bash
qmk compile -kb crkbd/rev1 -km r0nsha          # single compile
qmk userspace-compile                           # all targets in qmk.json
make crkbd/rev1:r0nsha                          # passthrough to qmk_firmware
just compile                                    # clean compile + bear (clangd)
just flash                                      # stock OLED build
just flash_trackpoint                           # trackpoint build
```

`Makefile` forwards every target to `qmk_firmware` (resolved via `qmk config -ro user.qmk_home`). `qmk.json` declares the single build target `crkbd/rev1:r0nsha`.

`just install` = first-time setup: pip-installs `qmk`, runs `qmk setup` against `holykeebs/qmk_firmware` branch `hk-master`, then `bear` compile. `just clone_firmware` clones that fork to `~/dev/qmk_firmware`.

## Dev setup

- Clangd needs `compile_commands.json`. Regenerate via `just compile` (or `just install`) after any config change. `compile_commands.json` is gitignored.
- `.devcontainer/` uses the `ghcr.io/qmk/qmk_cli` image; post-create clones `qmk/qmk_firmware` to `/workspaces/qmk_firmware` and sets `qmk config user.overlay_dir`.
- `qmk setup` (in `just install`) uses `holykeebs/qmk_firmware` branch `hk-master`, not upstream QMK `master`.

## Project layout

| Path | Purpose |
| --- | --- |
| `users/holykeebs/` | Shared pointing-device logic, EEPROM config, OLED, RPC sync, pimoroni/trackpoint drivers |
| `users/holykeebs/rules.mk` | ~600-line driver matrix. Selects `POINTING_DEVICE_DRIVER` + `OPT_DEFS` from `POINTING_DEVICE` + `POINTING_DEVICE_POSITION` env vars |
| `users/holykeebs/config.h` | Pin/route/feature defines; reads `HK_*` flags set by `rules.mk` |
| `keyboards/crkbd/rev1/keymaps/r0nsha/` | 8-layer keymap: QWERTY, COLEMAK, GAMING, EXT, SYM, NUM, FUN, MOUSE. Has RGB matrix, OLED, tap-dance, key overrides |
| `qmk.json` | Single build target: `crkbd/rev1:r0nsha` |
| `Justfile` | Flash + setup recipes |

## Build-time vars (set via `-e KEY=VAL` or `rules.mk`)

- `USER_NAME=holykeebs` (required; selects this user)
- `POINTING_DEVICE` — driver: `trackpoint`, `trackball` (pimoroni), `cirque35`, `cirque40`, `tps43`, `tps65`, or `a_b` combined pairs (e.g. `trackball_cirque35`, `tps43_trackpoint`)
- `POINTING_DEVICE_POSITION` = `right` | `left` | `thumb` | `thumb_inner` | `thumb_outer` | `middle`
- `OLED` = `stock` (standard crkbd OLED) | `yes` (custom holykeebs OLED + logo font, enables `HK_OLED_ENABLE`)
- `SPLIT_KEYBOARD=yes` enables `SERIAL_DRIVER=vendor`; `CONSOLE=yes` enables `CONSOLE_ENABLE`
- `SIDE=left|right` required for combined pointing devices
- `OLED_FLIP=yes`, `TRACKBALL_RGB_RAINBOW=yes` optional

`rules.mk` errors out with `CATASTROPHIC_ERROR` if `POINTING_DEVICE` is not in `VALID_POINTING_DEVICE_CONFIGURATIONS`.

## Custom keycodes (`users/holykeebs/holykeebs.h`)

| Keycode | Short alias | Function |
| --- | --- | --- |
| `HK_SAVE_SETTINGS` | `HK_SAVE` | Persist config to EEPROM |
| `HK_RESET_SETTINGS` | `HK_RESET` | Reset config to defaults (≠ `QK_CLEAR_EEPROM`) |
| `HK_DUMP_SETTINGS` | `HK_DUMP` | Log config to console (needs `CONSOLE_ENABLE=yes`) |
| `HK_SNIPING_MODE` | `HK_S_MODE` | Hold = sniping |
| `HK_SNIPING_MODE_TOGGLE` | `HK_S_MODE_T` | Toggle sniping |
| `HK_DRAGSCROLL_MODE` | `HK_D_MODE` | Hold = drag-scroll |
| `HK_DRAGSCROLL_MODE_TOGGLE` | `HK_D_MODE_T` | Toggle drag-scroll |
| `HK_CYCLE_SCROLL_LOCK` | `HK_C_SCROLL` | Cycle scroll-lock axis: off → H → V |
| `HK_INVERT_SCROLL_DIRECTION` | `HK_I_SCROLL` | Invert scroll |
| `HK_POINTER_SET_DEFAULT_SCALER` | `HK_P_SET_D` | Hold + `+`/`-` to scale default cursor |
| `HK_POINTER_SET_SNIPING_SCALER` | `HK_P_SET_S` | Same for sniping |
| `HK_POINTER_SET_SCROLL_BUFFER` | `HK_P_SET_BUF` | Adjust scroll accumulator |

Hold-shift on these keycodes targets the peripheral-side pointing device instead of main.

## EEPROM config (`users/holykeebs/eeprom_config.h`)

`hk_eeprom_config_t` union, 64 bytes (`EECONFIG_USER_DATA_SIZE`). Bitfields for cursor mode, drag-scroll, scroll-lock axis, multipliers, scroll buffer — duplicated for main + peripheral. Includes `check:1` and `version:8` for backward compat. Bump `version` on format change.

## Split sync

`users/holykeebs/rpc.c` uses QMK transaction API (`SPLIT_TRANSACTION_IDS_USER HK_SYNC_STATE`) when `HK_SPLIT_SYNC_STATE` is defined (= OLED enabled on split). `RPC_M2S_BUFFER_SIZE=64`. Tracks pointing-device state + a `last_key_str` string for OLED.

## CI

`.github/workflows/build_binaries.yaml` → reuses `qmk/.github` `qmk_userspace_build.yml@main` + `qmk_userspace_publish.yml@main`. Builds on push, publishes to GitHub Releases.

## VCS

Both `git` and `jj` work. `.jj/` at root.

## Code style

Google style clang-format, 4-space indent, pointers right-aligned, `ColumnLimit: 1000`. `Makefile`/`*.mk` use tabs (`.editorconfig`). `users/holykeebs/` uses `#pragma once` and `<stdint.h>` (not C99 mix).

## Common pitfalls

- Compiling without `POINTING_DEVICE` set still succeeds but `MASTER_SIDE` and driver logic fall through to defaults — set it explicitly for non-stock builds.
- `users/holykeebs/config.h` `#error`s if neither `HK_MASTER_LEFT` nor `HK_MASTER_RIGHT` is defined on a split board.
- After changing `rules.mk` / `config.h`, re-run `just compile` to refresh `compile_commands.json` for clangd.
- EEPROM layout changes must keep `check` + `version` handling or saved configs corrupt.
- Don't hot-plug the TRRS cable — `users/holykeebs/rules.mk` warns that it can short GPIO.
