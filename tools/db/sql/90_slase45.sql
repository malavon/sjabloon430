--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2032', 'SLASE45', 16,  8192, 1024, 60, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2033', 'SLASE45', 16, 16384, 2048, 60, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2032', 'ADC_SAR10', '10', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2032', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2032', 'IRML'     , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2033', 'ADC_SAR10', '10', NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2033', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430FR2033', 'IRML'     , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2032IG48' , 'MSP430FR2032', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2032IG48R', 'MSP430FR2032', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2032IG56' , 'MSP430FR2032', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2032IG56R', 'MSP430FR2032', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2032IPMR' , 'MSP430FR2032', 'PM' , 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2033IG48' , 'MSP430FR2033', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2033IG48R', 'MSP430FR2033', 'DGG', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2033IG56' , 'MSP430FR2033', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2033IG56R', 'MSP430FR2033', 'DGG', 56, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2033IPM'  , 'MSP430FR2033', 'PM' , 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430FR2033IPMR' , 'MSP430FR2033', 'PM' , 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
