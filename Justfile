set unstable

common := "-e USER_NAME=holykeebs -kb crkbd/rev1 -km r0nsha"

pd_args(pd) := if pd == "" {
    "-e OLED=stock"
} else {
    "-e OLED=yes -e POINTING_DEVICE=" + pd + " -e POINTING_DEVICE_POSITION=right"
}

compile pd="":
    make clean; bear -- qmk compile {{common}} {{ pd_args(pd) }}

flash pd="":
    cd ~/dev/qmk_firmware && qmk flash -j8 {{common}} {{ pd_args(pd) }}

install:
    #!/usr/bin/env bash
    if ! command -v qmk &> /dev/null; then
        python3 -m pip install --user qmk
    fi
    mkdir -p ~/dev
    qmk setup --home ~/dev/qmk_firmware -b hk-master holykeebs/qmk_firmware

clone_firmware:
    git clone --recurse-submodules https://github.com/holykeebs/qmk_firmware.git ~/dev/qmk_firmware -b hk-master
    # cd ~/dev/qmk_firmware
    # mkdir -p modules
    # git submodule add https://github.com/getreuer/qmk-modules.git modules/getreuer
    # git submodule update --init --recursive

