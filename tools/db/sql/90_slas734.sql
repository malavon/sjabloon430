--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2203', 'SLAS734', 16,  2048, 256, 24, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233', 'SLAS734', 16,  2048, 256, 24, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2303', 'SLAS734', 16,  4096, 256, 24, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333', 'SLAS734', 16,  4096, 256, 24, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403', 'SLAS734', 16,  8192, 512, 24, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433', 'SLAS734', 16,  8192, 512, 24, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533', 'SLAS734', 16, 16384, 512, 24, 1, 0, 1, 2, 0, 2, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2203', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2233', 'ADC_SAR10', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2233', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2303', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2333', 'ADC_SAR10', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2333', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2403', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2433', 'ADC_SAR10', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2433', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2533', 'ADC_SAR10', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('MSP430G2533', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2203IN20'   , 'MSP430G2203', 'N'  , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2203IPW20'  , 'MSP430G2203', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2203IPW20R' , 'MSP430G2203', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2203IPW28'  , 'MSP430G2203', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2203IPW28R' , 'MSP430G2203', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2203IRHB32R', 'MSP430G2203', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233IN20'   , 'MSP430G2233', 'N'  , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233IPW20'  , 'MSP430G2233', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233IPW20R' , 'MSP430G2233', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233IPW28'  , 'MSP430G2233', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233IPW28R' , 'MSP430G2233', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233IRHB32R', 'MSP430G2233', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2233IRHB32T', 'MSP430G2233', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2303IPW20'  , 'MSP430G2303', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2303IPW20R' , 'MSP430G2303', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2303IPW28'  , 'MSP430G2303', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2303IPW28R' , 'MSP430G2303', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2303IRHB32R', 'MSP430G2303', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2303IRHB32T', 'MSP430G2303', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333IN20'   , 'MSP430G2333', 'N'  , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333IPW20'  , 'MSP430G2333', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333IPW20R' , 'MSP430G2333', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333IPW28'  , 'MSP430G2333', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333IPW28R' , 'MSP430G2333', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333IRHB32R', 'MSP430G2333', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2333IRHB32T', 'MSP430G2333', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403IN20'   , 'MSP430G2403', 'N'  , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403IPW20'  , 'MSP430G2403', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403IPW20R' , 'MSP430G2403', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403IPW28'  , 'MSP430G2403', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403IPW28R' , 'MSP430G2403', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403IRHB32R', 'MSP430G2403', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2403IRHB32T', 'MSP430G2403', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433IN20'   , 'MSP430G2433', 'N'  , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433IPW20'  , 'MSP430G2433', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433IPW20R' , 'MSP430G2433', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433IPW28'  , 'MSP430G2433', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433IPW28R' , 'MSP430G2433', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433IRHB32R', 'MSP430G2433', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2433IRHB32T', 'MSP430G2433', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533IN20'   , 'MSP430G2533', 'N'  , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533IPW20'  , 'MSP430G2533', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533IPW20R' , 'MSP430G2533', 'PW' , 20, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533IPW28'  , 'MSP430G2533', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533IPW28R' , 'MSP430G2533', 'PW' , 28, 'ACTIVE', 1, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533IRHB32R', 'MSP430G2533', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('MSP430G2533IRHB32T', 'MSP430G2533', 'RHB', 32, 'ACTIVE', 2, -40, 85, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
