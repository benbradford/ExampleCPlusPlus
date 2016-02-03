#pragma once

#include <vector>
#include <functional>
#include <unordered_map>
#include <unordered_set>

class Piece;

using PieceId = int;

class Piece
{
public:
	struct AlreadyAttachedException{};
	struct AlreadyDetachedException{};
	struct SamePieceException{};

	Piece(PieceId id) : mId(id) {}
	Piece(Piece&&) noexcept = default;

	PieceId GetId() const noexcept { return mId; }
	bool 	IsAttachedTo(PieceId pieceId) const noexcept;

	static void Attach(Piece& p1, Piece& p2);
	static void Detach(Piece& p1, Piece& p2);
	
private:	
	PieceId mId;
	std::unordered_set<PieceId> mConnectedTo;
};

class Jigsaw
{
public:
	struct AddPieceNoConnectionsException{};
	struct CanConnectNoConnectionException{};
	struct ValidationException{};
	struct ValidationMissingPieceException : ValidationException{};
	struct ValidationMissingConnectionException : ValidationException{};
	struct ValidationConnectionsDoNotMatchException : ValidationException{};
	struct ValidationConnectionToSelfException : ValidationException{};

	Jigsaw() = default;
	Jigsaw(Jigsaw&&) noexcept = default;
	
	void AddPiece(PieceId pieceId, const std::vector<PieceId>& connectsTo);
	bool Attach(PieceId p1, PieceId p2);
	bool Detach(PieceId p1, PieceId p2);
	bool IsSolved() const noexcept;
	bool HasConnection(PieceId piece1, PieceId piece2) const noexcept;
	void Validate() const;

private:	
	// ordering is not important, so we use unordered containers
	using ConnectionMap = std::unordered_map<PieceId, std::unordered_set<PieceId>>;
	using PieceMap = std::unordered_map<PieceId, Piece>;

	PieceMap	  mPieceMap;		// all pieces
	ConnectionMap mConnectionMap;	// all possible connections

};