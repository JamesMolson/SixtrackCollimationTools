#	ADD_TEST(NAME ${TEST} WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Tests/${TEST} COMMAND BeamLossPattern)

	#Test what happens if the each program is run with no input files given
	ADD_TEST(NAME RunBeamLossPattern COMMAND BeamLossPattern)
	set_tests_properties(RunBeamLossPattern PROPERTIES PASS_REGULAR_EXPRESSION "Some input is missing!\nThe command line should look like:\n-> .*BeamLossPattern inj tracks2\\.dat output\\.txt ApertureFile\\.txt <-")

	ADD_TEST(NAME RunCleanInelastic COMMAND CleanInelastic)
	set_tests_properties(RunCleanInelastic PROPERTIES PASS_REGULAR_EXPRESSION "Some input is missing!\nThe command line should look like:\n-> .*CleanInelastic Impact\\.file Loss\\.file Coll\\.positions coll_summary file <-")

	ADD_TEST(NAME RunCountNabs COMMAND CountNabs)
	set_tests_properties(RunCountNabs PROPERTIES PASS_REGULAR_EXPRESSION "Some input is missing!\nThe command line should look like:\n-> .*CountNabs s1 tracks2\\.dat EN optics <-")

	ADD_TEST(NAME RunGetAperture COMMAND GetAperture)
	set_tests_properties(RunGetAperture PROPERTIES PASS_REGULAR_EXPRESSION "ERROR in the input definition!\nCommand line should look like:\n-> .*GetAperture ApertureFile\\.dat <-")

	#Test what happens if the input files are missing
	ADD_TEST(NAME BeamLossPatternMissingInput1 COMMAND BeamLossPattern inj tracks2.dat output.txt ApertureFile.txt)
	set_tests_properties(BeamLossPatternMissingInput1 PROPERTIES PASS_REGULAR_EXPRESSION ".*Could not open input aperture file: ApertureFile.txt")
