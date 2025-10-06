import os
import subprocess

mcu_bridge_hw = "stm32"

mcu_bridge_mcu_g0_version = [
    "stm32g0b1xx",
    "stm32g0c1xx",
    "stm32g0b0xx",
    "stm32g071xx",
    "stm32g081xx",
    "stm32g070xx",
    "stm32g031xx",
    "stm32g041xx",
    "stm32g030xx",
    "stm32g051xx",
    "stm32g061xx",
    "stm32g050xx",
]

mcu_bridge_mcu_g4_version = [
    "stm32g474xx",
    "stm32g431xx",
    "stm32g441xx",
    "stm32g471xx",
    "stm32g473xx",
    "stm32g483xx",
    "stm32g474xx",
    "stm32g484xx",
    "stm32g491xx",
    "stm32g4a1xx",
    "stm32gbk1cb",
    "stm32g411xb",
    "stm32g411xc",
    "stm32g414xx",
]

mcu_bridge_mcu_f0_version = [
    "stm32f030x6",
    "stm32f030x8",
    "stm32f031x6",
    "stm32f038xx",
    "stm32f042x6",
    "stm32f048xx",
    "stm32f051x8",
    "stm32f058xx",
    "stm32f070x6",
    "stm32f070xb",
    "stm32f071xb",
    "stm32f072xb",
    "stm32f078xx",
    "stm32f091xc",
    "stm32f098xx",
    "stm32f030xc",
]

mcu_bridge_mcu_f1_version = [
    "stm32f100xb",
    "stm32f100xe",
    "stm32f101x6",
    "stm32f101xb",
    "stm32f101xe",
    "stm32f101xg",
    "stm32f102x6",
    "stm32f102xb",
    "stm32f103x6",
    "stm32f103xb",
    "stm32f103xe",
    "stm32f103xg",
    "stm32f105xc",
    "stm32f107xc",
]

mcu_bridge_mcu_dict = {
    "stm32g0xx": mcu_bridge_mcu_g0_version,
    "stm32g4xx": mcu_bridge_mcu_g4_version,
    "stm32f0xx": mcu_bridge_mcu_f0_version,
    "stm32f1xx": mcu_bridge_mcu_f1_version,
}

log_dir = "build_logs/stm32"
os.makedirs(log_dir, exist_ok=True)

def run_and_log(cmd: str, log_file: str) -> int:
    with open(log_file, "a") as f:
        f.write(f"\n$ {cmd}\n")
        process = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
        for line in process.stdout:
            print(line, end='')   # Print to stdout
            f.write(line)         # Write to log file
        process.wait()
    return process.returncode

def test_stm32_build():
    status = 0
    for each_family in mcu_bridge_mcu_dict.keys():
        log_file = os.path.join(log_dir, f"{each_family}_family.log")

        status += run_and_log(f"make remove-stm32-family MCU_BRIDGE_MCU={each_family}", log_file)
        if status != 0:
            print("Failed to remove existing STM32 family. See log:", log_file)
            assert False

        status += run_and_log(f"make add-stm32-family MCU_BRIDGE_MCU={each_family}", log_file)
        if status != 0:
            print("Failed to add STM32 family. See log:", log_file)
            assert False

        for each_version in mcu_bridge_mcu_dict[each_family]:
            log_file = os.path.join(log_dir, f"{each_version}.log")
            status += run_and_log(
                f"make -j4 mcu_bridge MCU_BRIDGE_HW={mcu_bridge_hw} MCU_BRIDGE_MCU={each_family} MCU_BRIDGE_MCU_VERSION={each_version}",
                log_file
            )
            if status != 0:
                print(f"Failed to build for {each_version}. See log:", log_file)
                assert False

            status += run_and_log("make clean", log_file)
            if status != 0:
                print(f"Failed to clean for {each_version}. See log:", log_file)
                assert False

# Main
test_stm32_build()