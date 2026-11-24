#include "gtest/gtest.h"
#include "../../task-2/model/Universe.h"

namespace {
	constexpr int fieldSize = 20;

	vector<vector<bool>> emptyField() {
		return vector<vector<bool>>(fieldSize, vector<bool>(fieldSize, false));
	}

	Universe makeUniverse(const vector<vector<bool>> &field) {
		return Universe(field, vector<int>{3}, vector<int>{2, 3}, fieldSize, fieldSize, "test");
	}
}

TEST(UniverseTests, DefaultConstructorCreatesGliderAtTickZero) {
	Universe universe;

	EXPECT_EQ(universe.getCurrentTick(), 0);
	EXPECT_EQ(universe.getField().size(), fieldSize);
	EXPECT_EQ(universe.getField()[0].size(), fieldSize);
	EXPECT_TRUE(universe.getCell(1, 0));
	EXPECT_TRUE(universe.getCell(2, 1));
	EXPECT_TRUE(universe.getCell(0, 2));
	EXPECT_FALSE(universe.getCell(0, 0));
}

TEST(UniverseTests, CustomConstructorStoresNameAndRules) {
	vector<vector<bool>> field = emptyField();
	Universe universe(field, vector<int>{3, 6}, vector<int>{2, 3}, fieldSize, fieldSize, "custom");

	EXPECT_EQ(universe.name, "custom");
	EXPECT_EQ(universe.getBirth(), (vector<int>{3, 6}));
	EXPECT_EQ(universe.getSurvival(), (vector<int>{2, 3}));
	EXPECT_EQ(universe.getCurrentTick(), 0);
}

TEST(UniverseTests, SetCellUpdatesCellState) {
	Universe universe;

	universe.setCell(7, 9, true);
	EXPECT_TRUE(universe.getCell(7, 9));

	universe.setCell(7, 9, false);
	EXPECT_FALSE(universe.getCell(7, 9));
}

TEST(UniverseTests, SetCellThrowsForOutOfBoundsCoordinates) {
	Universe universe;

	EXPECT_THROW(universe.setCell(-1, 0, true), std::out_of_range);
	EXPECT_THROW(universe.setCell(0, fieldSize, true), std::out_of_range);
}

TEST(UniverseTests, GetCellThrowsForOutOfBoundsCoordinates) {
	Universe universe;

	EXPECT_THROW(universe.getCell(fieldSize, 0), std::out_of_range);
	EXPECT_THROW(universe.getCell(0, -1), std::out_of_range);
}

TEST(UniverseTests, TickBirthsCellWithThreeNeighbors) {
	vector<vector<bool>> field = emptyField();
	field[9][10] = true;
	field[10][9] = true;
	field[11][10] = true;
	Universe universe = makeUniverse(field);

	universe.tick();

	EXPECT_TRUE(universe.getCell(10, 10));
	EXPECT_EQ(universe.getCurrentTick(), 1);
}

TEST(UniverseTests, TickKillsCellWithFewerThanTwoNeighbors) {
	vector<vector<bool>> field = emptyField();
	field[10][10] = true;
	Universe universe = makeUniverse(field);

	universe.tick();

	EXPECT_FALSE(universe.getCell(10, 10));
}

TEST(UniverseTests, TickKillsCellWithMoreThanThreeNeighbors) {
	vector<vector<bool>> field = emptyField();
	field[10][10] = true;
	field[9][9] = true;
	field[9][10] = true;
	field[9][11] = true;
	field[10][9] = true;
	Universe universe = makeUniverse(field);

	universe.tick();

	EXPECT_FALSE(universe.getCell(10, 10));
}

TEST(UniverseTests, TickTwoPreservesBlinkerAndAdvancesGenerationTwice) {
	vector<vector<bool>> field = emptyField();
	field[10][9] = true;
	field[10][10] = true;
	field[10][11] = true;
	Universe universe = makeUniverse(field);

	universe.tick(2);

	EXPECT_TRUE(universe.getCell(9, 10));
	EXPECT_TRUE(universe.getCell(10, 10));
	EXPECT_TRUE(universe.getCell(11, 10));
	EXPECT_FALSE(universe.getCell(10, 9));
	EXPECT_FALSE(universe.getCell(10, 11));
	EXPECT_EQ(universe.getCurrentTick(), 2);
}

TEST(UniverseTests, FieldStringContainsHeaderAndCanOmitIt) {
	Universe universe;
	const string withHeader = universe.getFieldAsString();
	const string withoutHeader = universe.getFieldAsString(false);

	EXPECT_NE(withHeader.find("Universe: Universe\nRuleset: B3/S23\nCurrent tick: 0\n"), string::npos);
	EXPECT_EQ(withoutHeader.size(), fieldSize * (fieldSize + 1));
	EXPECT_EQ(withoutHeader.find("Universe:"), string::npos);
}
