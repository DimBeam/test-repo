import random 



suits = ('Hearts', 'Diamonds', 'Spades', 'Clubs')
ranks = ('Two', 'Three', 'Four', 'Five', 'Six', 'Seven', 'Eight', 'Nine', 'Ten', 'Jack', 'Queen', 'King', 'Ace')
values = {'Two':2, 'Three':3, 'Four':4, 'Five':5, 'Six':6, 'Seven':7, 'Eight':8, 
            'Nine':9, 'Ten':10, 'Jack':11, 'Queen':12, 'King':13, 'Ace':14}


class Card:
    
    def __init__(self,suit,rank):
        self.suit = suit
        self.rank = rank
        self.value = values[rank]
        
    def __str__(self):
        return self.rank + ' of ' + self.suit



class Deck:
    
    def __init__(self):
        # Note this only happens once upon creation of a new Deck
        self.all_cards = [] 
        for suit in suits:
            for rank in ranks:
                # This assumes the Card class has already been defined!
                self.all_cards.append(Card(suit,rank))
                
    def shuffle(self):
        # Note this doesn't return anything
        random.shuffle(self.all_cards)
        
    def deal_one(self):
        # Note we remove one card from the list of all_cards
        return self.all_cards.pop()        




class Player():
    def __init__(self):
        self.cards_hand = []
        self.total_value=0
    
    def add_card(self,new_card):
        self.cards_hand.append(new_card)
        self.total_value+=new_card.value
    




print(mydeck.all_cards[0])




#Initialize and Deck and Player
mydeck=Deck()
dimitris=Player()
#Shuffle Deck
mydeck.shuffle() 

#player flow
stop=0
play=
while True:
 ##draw card from deck and add to players hand
 draw_card = mydeck.deal_one()
 dimitris.add_card(draw_card)
 
 if dimitris.total_value == 21:
     print('B L A C K J A C K !!!  WIN!!')
     stop=1
     break
 elif dimitris.total_value> 21:
     print('Over 21! Player Lose :(')
     stop=1
     break
 else:
     while play!='Y' and play!='N': 
         play=input(f'Total value is {dimitris.total_value} \nContinue Y/N ')
         
     if play == 'Y' :
         pass
     elif play=='N':
         break
     
print(f'Players hand = {dimitris.total_value}')
 
# computer game flow 
computer=Player()
while stop!=1:
 
 draw_card = mydeck.deal_one()
 computer.add_card(draw_card)

 if computer.total_value > 21: 
     
     print ('\tYOU WIN!')
     break
 elif computer.total_value > dimitris.total_value:
     print('\t Computer Win , player Lose :( ')
     break

print(f'\t\tPlayer total Value {dimitris.total_value} \t Computer total Value {computer.total_value}')




