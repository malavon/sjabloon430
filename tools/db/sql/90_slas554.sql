--
-- File generated with one of the sjabloon 430 database tools.
-- Any alterations to this data will be kept by these tools, assuming the SQL is still valid.
-- DO NOT REFORMAT THIS FILE AND CHECK IN ONLY AFTER RE-EXPORTING WITH A SJABLOON 430 TOOL.
--
-- Text encoding used: UTF-8
--
BEGIN TRANSACTION;

INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F5133', 'SLAS554', 20,  8192, 2048, 30, 1, 0, 1, 1, 6, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F5135', 'SLAS554', 20, 16384, 2048, 30, 1, 0, 1, 1, 6, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F5137', 'SLAS554', 20, 32768, 4096, 30, 1, 0, 1, 1, 6, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F6125', 'SLAS554', 20, 16384, 2048, 44, 1, 0, 1, 1, 8, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F6126', 'SLAS554', 20, 32768, 2048, 44, 1, 0, 1, 1, 8, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F6127', 'SLAS554', 20, 32768, 4096, 44, 1, 0, 1, 1, 8, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F6135', 'SLAS554', 20, 16384, 2048, 44, 1, 0, 1, 1, 8, 2, -40, 85, 'TI EXPORT');
INSERT INTO device (model, datasheet_id, freq_max, storage_bytes, ram_bytes, gpio_count, uart_count, usb_count, i2c_count, spi_count, comp_count, timer_count, op_temp_min, op_temp_max, comment) VALUES ('CC430F6137', 'SLAS554', 20, 32768, 4096, 44, 1, 0, 1, 1, 8, 2, -40, 85, 'TI EXPORT');

INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5133', 'ADC_SAR12', '6' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5133', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5133', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5135', 'ADC_SAR12', '6' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5135', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5135', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5137', 'ADC_SAR12', '6' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5137', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F5137', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6125', 'ADC_SLOPE', '0' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6125', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6125', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6126', 'ADC_SLOPE', '0' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6126', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6126', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6127', 'ADC_SLOPE', '0' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6127', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6127', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6135', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6135', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6135', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6137', 'ADC_SAR12', '8' , NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6137', 'BSL_UART' , NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');
INSERT INTO device_feature (device_id, feature_id, param1, param2, param3, comment) VALUES ('CC430F6137', 'ADV_SENSE', NULL, NULL, NULL, 'AUTOMATIC RESOLUTION');

INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5133IRGZ' , 'CC430F5133', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5133IRGZR', 'CC430F5133', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5133IRGZT', 'CC430F5133', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5135IRGZ' , 'CC430F5135', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5135IRGZR', 'CC430F5135', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5135IRGZT', 'CC430F5135', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5137IRGZ' , 'CC430F5137', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5137IRGZR', 'CC430F5137', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F5137IRGZT', 'CC430F5137', 'RGZ', 48, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F6125IRGCR', 'CC430F6125', 'RGC', 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F6126IRGCR', 'CC430F6126', 'RGC', 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F6127IRGCR', 'CC430F6127', 'RGC', 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F6127IRGCT', 'CC430F6127', 'RGC', 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F6135IRGCR', 'CC430F6135', 'RGC', 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F6137IRGCR', 'CC430F6137', 'RGC', 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');
INSERT INTO orderable (name, device_id, drawing, pins, status, msl_level, op_temp_min, op_temp_max, comment) VALUES ('CC430F6137IRGCT', 'CC430F6137', 'RGC', 64, 'ACTIVE', 3, -40, 85, 'AUTOMATIC RESOLUTION');

COMMIT TRANSACTION;
