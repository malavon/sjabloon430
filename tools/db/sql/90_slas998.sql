--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67621', 'SLAS998', 25,  65536, 4096, 72, 3, 0, 1, 4, 0, 4, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67641', 'SLAS998', 25, 131072, 8192, 72, 3, 0, 1, 4, 0, 4, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F67621', 'ADC_SD24' , '3' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F67621', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F67621', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F67641', 'ADC_SD24' , '3' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F67641', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430F67641', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67621IPN' , 'MSP430F67621', 'PN',  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67621IPNR', 'MSP430F67621', 'PN',  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67621IPZ' , 'MSP430F67621', 'PZ', 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67621IPZR', 'MSP430F67621', 'PZ', 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67641IPN' , 'MSP430F67641', 'PN',  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67641IPNR', 'MSP430F67641', 'PN',  80, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67641IPZ' , 'MSP430F67641', 'PZ', 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430F67641IPZR', 'MSP430F67641', 'PZ', 100, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
