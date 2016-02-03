#include "test/TestCommon.h"
#include "ExceptionSafety/Jigsaw.h"

Jigsaw CreateNinePiece()
{
	Jigsaw j;
	j.AddPiece(1, {2,4});
	j.AddPiece(2, {1,5,3});
	j.AddPiece(3, {2,6});
	j.AddPiece(4, {1,5,7});
	j.AddPiece(5, {4,2,6,8});
	j.AddPiece(6, {3,5,9});
	j.AddPiece(7, {4,8});
	j.AddPiece(8, {7,5,9});
	j.AddPiece(9, {8,6});
	return j;
}

Jigsaw CreateNinePieceError()
{
	Jigsaw j;
	j.AddPiece(1, {2,4});
	j.AddPiece(2, {1,5,3});
	j.AddPiece(3, {2,6});
	j.AddPiece(4, {1,5,7});
	j.AddPiece(5, {4,6,8}); // missing connection to 8
	j.AddPiece(6, {3,5,9});
	j.AddPiece(7, {4,8});
	j.AddPiece(8, {7,5,9});
	j.AddPiece(9, {8,6});
	return j;
}

TEST(TestJigsaw, CanCreate)
{
	Jigsaw j;
}

TEST(TestJigsaw, CanConnectTwoPieces)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1});
	ASSERT_NO_THROW(j.Validate());
}

TEST(TestJigsaw, NoSpecifyingConnectionsWillThrow)
{
	Jigsaw j;
	ASSERT_THROW(j.AddPiece(1,{}), Jigsaw::AddPieceNoConnectionsException);
}

TEST(TestJigsaw, ConnectionsNotMatchingWillThrow)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1});
	j.AddPiece(3, {1});
	ASSERT_THROW(j.Validate(), Jigsaw::ValidationConnectionsDoNotMatchException);

}

TEST(TestJigsaw, ConnectionsToSelfWillThrow)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1,2});
	ASSERT_THROW(j.Validate(), Jigsaw::ValidationConnectionToSelfException);

}

TEST(TestJigsaw, ConnectionsMissingWillThrow)
{
	Jigsaw j;
	j.AddPiece(1, {3});
	j.AddPiece(2, {3});
	ASSERT_THROW(j.Validate(), Jigsaw::ValidationMissingConnectionException);

}

TEST(TestJigsaw, MoreComplexConnectionValidation)
{
	Jigsaw j = CreateNinePiece();
	ASSERT_NO_THROW(j.Validate());
}

TEST(TestJigsaw, MoreComplexConnectionValidationSmallErrorThrows)
{
	Jigsaw j = CreateNinePieceError();
	ASSERT_THROW(j.Validate(), Jigsaw::ValidationException);
}

TEST(TestJigsaw, CanAttachTwoMatchingPieces)
{
	Jigsaw j = CreateNinePiece();
}

TEST(TestJigsaw, CanAttachTwoPieces)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1});
	ASSERT_NO_THROW(j.Attach(1,2));
}

TEST(TestJigsaw, CanDetachTwoPieces)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1});
	ASSERT_NO_THROW(j.Attach(1,2));
	ASSERT_NO_THROW(j.Detach(1,2));
}

TEST(TestJigsaw, CanDetachTwoPiecesSpecifiedInDifferentOrder)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1});
	ASSERT_NO_THROW(j.Attach(1,2));
	ASSERT_NO_THROW(j.Detach(2,1));
}

TEST(TestJigsaw, AttachingOrDetachingSamePieceWillThrow)
{
	Piece piece(1);
	ASSERT_THROW(Piece::Attach(piece,piece), Piece::SamePieceException);
	ASSERT_THROW(Piece::Detach(piece,piece), Piece::SamePieceException);
}

TEST(TestJigsaw, CannotAttachUnconnectedPieces)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {3});
	j.AddPiece(3, {2});
	ASSERT_FALSE(j.Attach(1,3));
}

TEST(TestJigsaw, CanSolveSimpleJigsaw)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1});
	j.Attach(1,2);
	ASSERT_TRUE(j.IsSolved());
}

TEST(TestJigsaw, NoAttachmentsMeansNotSolved)
{
	Jigsaw j;
	j.AddPiece(1, {2});
	j.AddPiece(2, {1});
	ASSERT_FALSE(j.IsSolved());
}

TEST(TestJigsaw, CanSolveComplexJigsaw)
{
	Jigsaw j = CreateNinePiece();
	ASSERT_NO_THROW(j.Attach(1,2));
	ASSERT_NO_THROW(j.Attach(1,4));
	ASSERT_NO_THROW(j.Attach(2,3));
	ASSERT_NO_THROW(j.Attach(2,5));
	ASSERT_NO_THROW(j.Attach(3,6));
	ASSERT_NO_THROW(j.Attach(4,5));
	ASSERT_NO_THROW(j.Attach(4,7));
	ASSERT_NO_THROW(j.Attach(5,6));
	ASSERT_NO_THROW(j.Attach(5,8));
	ASSERT_NO_THROW(j.Attach(6,9));
	ASSERT_NO_THROW(j.Attach(7,8));
	ASSERT_NO_THROW(j.Attach(8,9));
	ASSERT_TRUE(j.IsSolved());
}

TEST(TestJigsaw, OneAttachementMissingOfComplexWillNotSolve)
{
	Jigsaw j = CreateNinePiece();
	ASSERT_NO_THROW(j.Attach(1,2));
	ASSERT_NO_THROW(j.Attach(1,4));
	ASSERT_NO_THROW(j.Attach(2,3));
	ASSERT_NO_THROW(j.Attach(2,5));
	ASSERT_NO_THROW(j.Attach(3,6));
	ASSERT_NO_THROW(j.Attach(4,5));
	ASSERT_NO_THROW(j.Attach(4,7));
	ASSERT_NO_THROW(j.Attach(5,6));
	ASSERT_NO_THROW(j.Attach(5,8));
	ASSERT_NO_THROW(j.Attach(6,9));
	ASSERT_NO_THROW(j.Attach(7,8));
	//ASSERT_NO_THROW(j.Attach(8,9));
	ASSERT_FALSE(j.IsSolved());
}
