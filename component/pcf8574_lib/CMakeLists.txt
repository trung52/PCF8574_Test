set(app_src pcf8574_lib.c)
set(pre_req pcf8574)
idf_component_register(SRCS ${app_src}
                    INCLUDE_DIRS "."
                    REQUIRES ${pre_req})