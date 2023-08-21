set(COMPONENT_SRCS "adxl345.c")
idf_component_register(SRCS ${COMPONENT_SRCS}
    PRIV_REQUIRES driver
    INCLUDE_DIRS ".")