#ifndef CHAPTER_H
#define CHAPTER_H
#include <vector>
/**
* represent a chapter.
* work like a linked list
*/
class Chapter {
public:
	Chapter(short idealGoalId, short idealGoalPos, std::vector<short>  mapDist, short chapterIndex, short distPivotGoal)
		:idealGoalId(idealGoalId), idealGoalPos(idealGoalPos), mapDistanceFromGoal(mapDist), chapterIndex(chapterIndex) ,distPivotGoal(distPivotGoal) {}
	Chapter() {}

	short getIdealGoalId()const { return idealGoalId; };
	void setGoalId(short id) { idealGoalId = id; };

	short getIdealGoalPos()  ;
	void setGoalPos(short Pos) { idealGoalPos = Pos; };

	std::vector<short> getDistMap()const { return mapDistanceFromGoal; };
	void setDistMap(std::vector<short> map) { mapDistanceFromGoal = map; };

	short getIndex()const { return chapterIndex; };
	void setIndex(short index) { chapterIndex = index; };

	short getDistPivotGoal() const { return distPivotGoal; }
	void setDistPivotGoal(short dist) { distPivotGoal = dist; };

	Chapter* getNextChapter() { return nextChapter; };
	void setNextChapter(Chapter* snextChapter) { nextChapter = snextChapter; };


private:
	//id of the ideal goal of this chapter
	short  idealGoalId;
	//pos of the idealGOal of this chapter
	short idealGoalPos;
	//dist map from the idealGoal of this chapter
	std::vector<short> mapDistanceFromGoal;
	//index of ths chapter
	short chapterIndex;
	//distance beetween the current IdealGOal and the pivot point
	// use for ordering th e chapters
	short distPivotGoal;
	//pointer on the nex chapter
	Chapter *nextChapter;

};

#endif
