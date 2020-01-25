USE BookTrade
GO
CREATE PROCEDURE getIDCARTT
(
	@client_id AS INT
)
AS
	SELECT id FROM CARTT WHERE id = client_id
GO