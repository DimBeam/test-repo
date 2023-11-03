#!/usr/bin/env python
# coding: utf-8

# In[2]:


#functions
#prints the board (x for -1 , O for -2 , nothing if block is empty)
def printboard(board):
        for i in range (1,10):
            if (i-1)%3==0 and (i-1)!=0:
                print('\n',8*"-")
            if board[i-1]==-1:
                print(' X',end = '|')
            elif board[i-1]==-2:
                print(' O',end = '|')
            else:
                print(end = '  |')
#ask user to make move and apply change to board            
def makemove(board,player):
    #validating user input
    flag=True
    while flag==True:
        move=input(f'\n\n Player {player} chose a block ')
        if move.isdigit() == False:
            print('Wrong input. Please give a number, NOT a character')
        elif int(move) not in range(0,10):
            print('Wrong input . Give any number from 0 to 9')
        elif board[int(move)-1]!=0:
            print('You played on a marked block! Chose an empty one. ')
        else :
            move=int(move)
            flag=False
        
            
    if player==1:
        board[move-1]=-1
    if player==2:
        board[move-1]=-2
    

def wincheck(player):
    # check 
    
    ##horizontally
    for j in range(0,7,3):
        
        if board[j]==board[j+1] and board[j+1]==board[j+2] and board[j]!=0:
            print(f'\t CONGRATULATIONS!! PLAYER {player} WIN')
            return True
    #vertically
    for i in range (0,3):    
        if board[i]==board[i+3] and board[i+3]==board[i+6] and board[i]!=0:
            print(f'\t CONGRATULATIONS!! PLAYER {player} WIN')
            return True
    #diagonally
    if board[4]==board[8]==board[0] or board[4]==board[2]==board[6] and board[4]!=0:
        print(f'\t CONGRATULATIONS!! PLAYER {player} WIN')
        return True
def checkfull(board):
    for item in board:
        if item == 0:
            return False
    
    return True 


# In[ ]:





# In[3]:


#MAIN
global board
print('Welcome to TicTacToe')
newgame=input('Wanna start a Game Y/N \n')


if newgame=='y' or newgame=='Y':
    #Instructions
    print('Instructions: \n When is your turn ,type the number of the block (1-9) in which you want to play')
    print(' Player 1 is X || Player 2 is O')
    #Example
    board=[1,2,3,4,5,6,7,8,9]
    print('\n eg')
    for i in range (1,10):
            if (i-1)%3==0 and (i-1)!=0:
                print('\n',8*"-")
            print(f' {board[i-1]}',end = '|')
        
    
    #game start
    #clear board
    print("\n\nNow the game is staring . . . \n")
    board=[0]*9
    printboard(board)
    winner=0
    while winner==0:
       # player1 
        makemove(board,1)
        printboard(board)
        #check for win
        if wincheck(1) == True:
            break
        #check if board is full 
        if checkfull(board) == True:
            print('\t DRAW! Board is full. ')
            break
       
       # print('\n Player2 turn \n')
        makemove(board,2) 
        printboard(board)
        if wincheck(2) == True:
            break
        
        
        
        


# ##### 

# In[ ]:





# In[ ]:





# In[ ]:




