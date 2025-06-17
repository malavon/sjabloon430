--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2332-EP', 'SLAS885', 16, 4096, 256, 16, 0, 0, 1, 1, 0, 1, -40, 125, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2332-EP', 'ADC_SAR10', '8', NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2332QPW2EP' , 'MSP430G2332-EP', 'PW', 20, 'ACTIVE', 1, -40, 125, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2332QPW2REP', 'MSP430G2332-EP', 'PW', 20, 'ACTIVE', 1, -40, 125, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('V62/12625-01XE'    , 'MSP430G2332-EP', 'PW', 20, 'ACTIVE', 1, -40, 125, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('V62/12625-01XE-T'  , 'MSP430G2332-EP', 'PW', 20, 'ACTIVE', 1, -40, 125, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
