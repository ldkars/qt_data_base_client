USE BookTrade
GO
CREATE PROCEDURE BUE
(	
	@id as int,
	@book_id as int,
	@count as int
)
AS
	INSERT INTO CART_PRODUCT
	(
		id,
		book_id,
		count
    )
    VALUES (@id, @book_id, @count);
GO