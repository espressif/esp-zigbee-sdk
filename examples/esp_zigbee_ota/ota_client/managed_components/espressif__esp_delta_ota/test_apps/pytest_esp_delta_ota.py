import pytest


@pytest.mark.generic
def test_esp_delta_ota(dut) -> None:
    dut.run_all_single_board_cases()
