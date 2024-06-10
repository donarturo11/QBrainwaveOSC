#projectName(QBrainwaveOSC)
add_subdirectory(TwoByteRawParser)
set(DATAPARSERS_SOURCES
   ${CMAKE_CURRENT_SOURCE_DIR}/DataParser.h
   ${TWOBYTERAWPARSER_SOURCES}
   PARENT_SCOPE
   )
