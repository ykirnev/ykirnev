cards = {}
players = {}
while a:=input():
    parts = a.split(' / ')
    if len(parts) == 2:
        if parts[0][0].isalpha():
            player = parts[0]
            deck = int(parts[1])
            if player not in players:
                players[player] = set()
            players[player].add(deck)
        else:
            deck = int(parts[0])
            card = parts[1]
            if deck not in cards:
                cards[deck] = set()
            cards[deck].add(card)
mas_counts = {}
for player, decks in players.items():
    player_cards = set()
    for deck in decks:
        if deck in cards:
            player_cards.update(cards[deck])
    mas_counts[player] = len(player_cards)
mx = max(mas_counts.values())
max_players = [player for player, size in mas_counts.items() if size == mx]
for player in sorted(max_players):
    print(player)