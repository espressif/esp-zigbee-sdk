idf_component_register(SRC_DIRS "."
                       INCLUDE_DIRS ".")

# Tell esptool to flash the legacy NVRAM to the partition
set(partition_name "zb_storage")
set(partition_file "${PROJECT_DIR}/${partition_name}.legacy.bin")
partition_table_get_partition_info(partition_size "--partition-name ${partition_name}" "size")
file(SIZE "${partition_file}" partition_file_size)

if(NOT ${partition_file_size} EQUAL ${partition_size})
    message(FATAL_ERROR "Partition<${partition_name}> size (${partition_size}) "
                        "is not equal to file size (${partition_file_size})")
endif()

esptool_py_flash_to_partition(flash "${partition_name}" "${partition_file}")
