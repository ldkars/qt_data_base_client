USE BookTrade
GO
CREATE PROCEDURE insertGroupAuthor1(@book_id AS INT, @id AS INT)
AS
	INSERT INTO AUTHOR_GROUP (id, author_id1)
    VALUES (@book_id, @id);
GO

USE BookTrade
GO
CREATE PROCEDURE insertGroupAuthor2(@book_id AS INT, @id AS INT, @id2 AS INT)
AS
	INSERT INTO AUTHOR_GROUP (id, author_id1, author_id2)
    VALUES (@book_id, @id, @id2);
GO

USE BookTrade
GO
CREATE PROCEDURE insertGroupAuthor3(@book_id AS INT, @id AS INT, @id2 AS INT, @id3 AS INT)
AS
	INSERT INTO AUTHOR_GROUP (id, author_id1, author_id2, author_id3)
    VALUES (@book_id, @id, @id2, @id3);
GO

USE BookTrade
GO
CREATE PROCEDURE insertGroupAuthor4(@book_id AS INT, @id AS INT, @id2 AS INT, @id3 AS INT, @id4 AS INT)
AS
	INSERT INTO AUTHOR_GROUP (id, author_id1, author_id2, author_id3, author_id4)
    VALUES (@book_id, @id, @id2, @id3, @id4);
GO

USE BookTrade
GO
CREATE PROCEDURE insertGroupAuthor5(@book_id AS INT, @id AS INT, @id2 AS INT, @id3 AS INT, @id4 AS INT, @id5 AS INT)
AS
	INSERT INTO AUTHOR_GROUP (id, author_id1, author_id2, author_id3, author_id4, author_id5)
    VALUES (@book_id, @id, @id2, @id3, @id4, @id5);
GO



