USE BookTrade
DECLARE @TMP int;
SELECT @TMP = book_id FROM BOOK
WHERE book_id = (SELECT MAX(book_id) FROM BOOK)

USE BookTrade
GO
CREATE PROCEDURE getID
AS
	DECLARE @TMP int;
	SELECT @TMP = book_id FROM BOOK
	WHERE book_id = (SELECT MAX(book_id) FROM BOOK)

	SELECT book_id FROM BOOK
	WHERE book_id  = @TMP;
GO
