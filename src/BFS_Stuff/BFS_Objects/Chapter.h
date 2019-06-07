#ifndef CHAPTER_H
#define CHAPTER_H
/**
 * \file Chapter.h
 * \brief declaration of the class chapter
 * \author Romain Michau
 * \version 2.1
 */

#include <vector>

/** \class Chapter
 *  \brief Represent a step of the resolution of the game

 *  Each chapter is define by an ideal Goal, this is the goal to reach during this step.
 *  There is one Chapter by Goal.
 *  Chapter are ordering like that: farest is the goal, first will be treat the corresponding Chapter
 *  The CHapter is linked to the next chapter, so when the ideal Goal is reached, then we can access to the next Chapter * \n
 * Chapters are calculated at the beginning of the resolution
 */
class Chapter
{

private:

    const short  idealGoalId;/**< ID of the ideal goal of this Chapter */
    const short idealGoalPos;/**< Position of the ideal goal of this chapter */
    short chapterIndex;/**< Index of this chapter */
    const short distPivotGoal/**< Distance beetween the IdealGoal of this chapter and the pivot point */;
    Chapter *nextChapter;/**< Pointer to the next chapter of the game */

public:

    /** \brief Constructor of the class Chapter
     *
     * \param idealGoalId: id of the ideal goal of the chapter
     * \param idealGoalPos: position of the ideal goal
     * \param chapterIndex: index of the chapter
     * \param distPivotGoal: distance between the Pivot point of the maze and the ideal Goal of this Chapter
     *
     */
    Chapter(short idealGoalId, short idealGoalPos, short chapterIndex, short distPivotGoal)
        :idealGoalId(idealGoalId), idealGoalPos(idealGoalPos), chapterIndex(chapterIndex), distPivotGoal(distPivotGoal) {}

    /** \brief Default constructor of the class Chapter
     *  give default value to
     */
    Chapter()
        :idealGoalId(-1), idealGoalPos(-1), chapterIndex(-1), distPivotGoal(-1) {}


public:
    /** \brief Destructor of the class Chapter
     *  Does nothing special
     */
    ~Chapter() {}

    /** \brief getter of idealGoalId
     *
     * \return return idealGoalId
     *
     */
    short getIdealGoalId()const
    {
        return idealGoalId;
    };

    /** \brief getter of idealGoalPos
     *
     * \return idealGoalPos
     *
     */
    short getIdealGoalPos()const
    {
        return idealGoalPos;
    };

    /** \brief getter of chapterIndex
     *
     * \return chapterIndex
     *
     */
    short getIndex()const
    {
        return chapterIndex;
    };

    /** \brief setter of index
     *
     * \param index: new index of this chapter
     *
     */
    void setIndex(short index)
    {
        chapterIndex = index;
    };

    /** \brief getter of distPivotGoal
     *
     * \return distPivotGoal
     *
     */
    short getDistPivotGoal()const
    {
        return distPivotGoal;
    };

    /** \brief nextChapter
     *
     * \return the next nextChapter
     *
     */
    Chapter* getNextChapter()
    {
        return nextChapter;
    };

    /** \brief setter of nextChapter
     *
     * \param snextChapter new next chapter of the chapter
     *
     */
    void setNextChapter(Chapter* snextChapter)
    {
        nextChapter = snextChapter;
    };
};

#endif
