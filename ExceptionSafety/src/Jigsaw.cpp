#include "ExceptionSafety/Jigsaw.h"
#include <cassert>

void Piece::Attach(Piece& p1, Piece& p2)
{
	if(p1.mId == p2.mId)
		throw SamePieceException{};

	if (p1.mConnectedTo.find(p2.mId) != p1.mConnectedTo.end())
		throw AlreadyAttachedException{};

	p1.mConnectedTo.insert(p2.mId);
	try 
	{
		p2.mConnectedTo.insert(p1.mId);
	}
	catch(...)
	{
		p1.mConnectedTo.erase(p1.mConnectedTo.find(p2.mId));
		throw;
	}
}

void Piece::Detach(Piece& p1, Piece& p2)
{
	if(p1.mId == p2.mId)
		throw SamePieceException{};
	
	if (p1.mConnectedTo.find(p2.mId) == p1.mConnectedTo.end())
		throw AlreadyDetachedException{};

	const auto itToEraseFromP1 = p1.mConnectedTo.find(p2.mId);
	const auto itToEraseFromP2 = p2.mConnectedTo.find(p1.mId);
	
	if (itToEraseFromP1 != p1.mConnectedTo.end())
		p1.mConnectedTo.erase(itToEraseFromP1);
	
	if (itToEraseFromP2 != p2.mConnectedTo.end())
		p2.mConnectedTo.erase(itToEraseFromP2);
}

bool Piece::IsAttachedTo(PieceId pieceId) const noexcept
{
	return mConnectedTo.find(pieceId) != mConnectedTo.end();
}

// ======================================

void Jigsaw::AddPiece(PieceId pieceId, const std::vector<PieceId>& connectsTo)
{
	if (connectsTo.size() == 0)
		throw AddPieceNoConnectionsException{};
	auto pieceToInsert = std::make_pair(pieceId, Piece(pieceId));
	try 
	{
		auto& piecesToConnect = mConnectionMap[pieceId];
		for (auto otherId : connectsTo)
		{
			piecesToConnect.insert(otherId);
		}

		mPieceMap.emplace(std::move(pieceToInsert));
	}
	catch (...)
	{
		auto it = mConnectionMap.find(pieceId);
		if (it != mConnectionMap.end())
			mConnectionMap.erase(it);
		throw;
	}
	
}

bool Jigsaw::Attach(PieceId p1, PieceId p2)
{
	if (!HasConnection(p1, p2))
	{
		return false;
	}

	Piece::Attach(mPieceMap.find(p1)->second, mPieceMap.find(p2)->second);
	return true;
}

bool Jigsaw::Detach(PieceId p1, PieceId p2)
{
	if (!HasConnection(p1, p2))
	{
		return false;
	}

	Piece::Detach(mPieceMap.find(p1)->second, mPieceMap.find(p2)->second);
	return true;
}

bool Jigsaw::IsSolved() const noexcept
{
	for (auto it = mConnectionMap.begin(); it != mConnectionMap.end(); ++it)
	{
		const auto pieceIt = mPieceMap.find(it->first);
		assert(pieceIt != mPieceMap.end());
		for (auto requiredPiece : it->second)
		{
			if (pieceIt->second.IsAttachedTo(requiredPiece) == false)
				return false;
		}
	}
	return true;
}

bool Jigsaw::HasConnection(PieceId piece1, PieceId piece2) const noexcept
{
	const auto p1It = mConnectionMap.find(piece1);
	if (p1It == mConnectionMap.end() || mConnectionMap.find(piece2) == mConnectionMap.end())
		throw CanConnectNoConnectionException{};

	const auto p2It = p1It->second.find(piece2);
	return p2It != p1It->second.end();
}

void Jigsaw::Validate() const
{
	for (const auto& pieceIt : mPieceMap)
	{
		const auto pieceId1 = pieceIt.first;
		const auto connectionsFor1 = mConnectionMap.find(pieceId1);

		if (connectionsFor1 == mConnectionMap.end())
			throw ValidationMissingPieceException{};

		if (connectionsFor1->second.find(pieceId1) != connectionsFor1->second.end())
			throw ValidationConnectionToSelfException{};

		for (const auto& pieceId2 : connectionsFor1->second)
		{
			auto othersConnections = mConnectionMap.find(pieceId2);

			if (othersConnections == mConnectionMap.end())
				throw ValidationMissingConnectionException{};

			if (othersConnections->second.find(pieceId1) == othersConnections->second.end())
				throw ValidationConnectionsDoNotMatchException{};
		}
	}
}