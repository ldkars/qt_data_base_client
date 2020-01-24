USE BookTrade
GO
CREATE PROCEDURE insertBook
(
	@named as nchar(100),
	@price as float,
	@type_id as int,
	@House_id as int,
	@category_id as int,
	@description as nvarchar(max)
)
AS
	declare @new_id int
	SELECT @new_id = book_id + 1 FROM BOOK
	WHERE book_id = (SELECT MAX(book_id) FROM BOOK)	
	
	INSERT INTO BOOK 
	(
		book_id,
		named, 
		price, 
		type_id, 
		publishingHouse_id, 
		category_id,
		description
	)
    VALUES (@new_id, @named, @price, @type_id, @House_id, @category_id, @description);

	PRINT @new_id;
GO

--USE BookTrade
--ALTER TABLE BOOK ALTER COLUMN author_group_id int null;
