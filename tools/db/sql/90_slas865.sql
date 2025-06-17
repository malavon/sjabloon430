--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4131', 'SLAS865', 16,  4096,  512, 60, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4132', 'SLAS865', 16,  8192, 1024, 60, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4133', 'SLAS865', 16, 16384, 2048, 60, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4131', 'ADC_SAR10', '10', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4131', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4131', 'IRML'     , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4132', 'ADC_SAR10', '10', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4132', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4132', 'IRML'     , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4133', 'ADC_SAR10', '10', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4133', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR4133', 'IRML'     , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4131IG48' , 'MSP430FR4131', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4131IG48R', 'MSP430FR4131', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4131IG56' , 'MSP430FR4131', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4131IG56R', 'MSP430FR4131', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4131IPMR' , 'MSP430FR4131', 'PM' , 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4132IG48' , 'MSP430FR4132', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4132IG48R', 'MSP430FR4132', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4132IG56' , 'MSP430FR4132', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4132IG56R', 'MSP430FR4132', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4132IPMR' , 'MSP430FR4132', 'PM' , 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4133IG48' , 'MSP430FR4133', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4133IG48R', 'MSP430FR4133', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4133IG56' , 'MSP430FR4133', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4133IG56R', 'MSP430FR4133', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4133IPM'  , 'MSP430FR4133', 'PM' , 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR4133IPMR' , 'MSP430FR4133', 'PM' , 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
