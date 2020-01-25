USE BookTrade
GO
CREATE PROCEDURE createCart
(
	@client_id AS INT,
	@date AS INT
)
AS
	declare @new_id int
	SELECT @new_id = id + 1 FROM CARTT
	WHERE id = (SELECT MAX(id) FROM CARTT)	

	INSERT INTO CARTT
	(
		id,
		client_id,
		date
    )
    VALUES (@new_id, @client_id, @date);
GO