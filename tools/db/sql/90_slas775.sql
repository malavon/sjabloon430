--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2201-Q1', 'SLAS775', 16, 131072, 2048, 0, 0, 0, 0, 1, 0, 1, -40, 85, 'TI EXPORT');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2201IRSARQ1', 'MSP430G2201-Q1', 'RSA', 16, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
