%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% tab.pro - Lógica e Validação                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
% Neste ficheiro encontrão-se as intruções de validação e lógica de        %
% jogadas e do jogo.                                                       %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:- module(validationGame, [
	  
      placePieceTurn/3,
      gameplay/1,
      gameplayHvAI/2,
      verifyTerrain/5,
	  verifyMove/6,
      bestMove/6,
      gameplayAI/1
]).

:- use_module('tab.pro').
:- use_module(library(random)).

placePieceTurn(Turn, T, NT):-
        pieceList(PI),
        (
           (
              Turn = a,
              Name = 'A'
           );(
              Turn = b,
              Name = 'B'
           )
        ),
        clearScreen,
        castles(Turn,Name,T,Tab1),
        clearScreen,
        pieces(Turn,Name,PI,Tab1,NT).

menuGreen(Tab, E, X-Y, Tab2):-
        write('   1'),nl,
        write('   |'),nl,
        write('2- C -3'),nl,
        write('   |'),nl,
        write('   4'),nl,
        write('Place your Green: '),read(C),
        sizePTabH(H),
        sizeTabW(W),
        (
           (
              C = 1,!,
              (
                 (
                    Y > 1,!,
                    NY is Y - 1,
                    put(Tab,[g-E]-v-v-1,[],[],X,NY,Tab2)
                 );(
                    clearScreen,
                    write('No space for Green in this direction ('),write(C),write(') !'),nl,
                    menuGreen(Tab, E, X-Y, Tab2)
                 )
              )
           );(
              C = 2,!,
              (
                 (
                    X > 1,!,
                    NX is X - 1,
                    put(Tab,[g-E]-v-v-1,[],[],NX,Y,Tab2)
                 );(
                    clearScreen,
                    write('No space for Green in this direction ('),write(C),write(') !'),nl,
                    menuGreen(Tab, E, X-Y, Tab2)
                 )
              )
           );(
              C = 3,!,
              (
                 (
                    X < W,!,
                    NX is X + 1,
                    put(Tab,[g-E]-v-v-1,[],[],NX,Y,Tab2)
                 );(
                    clearScreen,
                    write('No space for Green in this direction ('),write(C),write(') !'),nl,
                    menuGreen(Tab, E, X-Y, Tab2)
                 )
              )
           );(
              C = 4,!,
              (
                 (
                    Y < H,!,
                    NY is Y + 1,
                    put(Tab,[g-E]-v-v-1,[],[],X,NY,Tab2)
                 );(
                    clearScreen,
                    write('No space for Green in this direction ('),write(C),write(') !'),nl,
                    menuGreen(Tab, E, X-Y, Tab2)
                 )
              )
           );(
                clearScreen,
                write('Not a valid choice!'),nl,
                menuGreen(Tab, E, X-Y, Tab2)
           )
        ).

castles(E,En,Tab,NT):-                
                nl,write('Player '),write(En),write(' place your ' ),write('Castle'),write(' (X-Y): '),read(X-Y),
                sizePTabH(H),
                sizeTabW(W),
                (
                   X =< W, X >= 1,
                   Y =< H, Y >= 1,!,
                   put(Tab,[c-E]-v-v-1,[],[],X,Y,Tab2),
                   (
                      menuGreen(Tab2, E, X-Y, NT)
                   )
                );(
                     clearScreen,
                     write('Not a valid coordinates!'),nl,
                     castles(E,En,Tab,NT)
                ).

pieces(_,_,[],T,T).
pieces(E,En,[[Piece-Number-Name-HV-Dia]|Rest],Tab,Tab1):-
                %nl,showTab(Tab),
                nl,write('Player '),write(En),write(': Place your ' ),write(Name),write(' (X-Y): '),
                read(X-Y),
                sizePTabH(H),
                sizeTabW(W),
                (
                   X =< W, X >= 1,
                   Y =< H, Y >= 1,
                   find(Tab,Terrain-v-v-_, X-Y),!,
                   (
                      (
                         (Piece = ki; Piece = d; Piece = p),!,
                         (
                                 (
                                    Terrain \= r, Terrain \= m,!,
                                    place(Tab,E-Piece-Number,X,Y,Tab2),
                                    pieces(E,En,Rest,Tab2,Tab1)
                                 );(
                                    clearScreen,
                                    write('Mountain or Rough Terrain located on those coordinates!'),nl,
                                    pieces(E,En,[[Piece-Number-Name-HV-Dia]|Rest],Tab,Tab1)
                                 )
                         )
                      );(
                         (Piece = k; Piece = se; Piece = pi),!,
                         (
                                 (
                                    Terrain \= m,!,
                                    place(Tab,E-Piece-Number,X,Y,Tab2),
                                    pieces(E,En,Rest,Tab2,Tab1)
                                 );(
                                    clearScreen,
                                    write('Mountain Terrain located on those coordinates!'),nl,
                                    pieces(E,En,[[Piece-Number-Name-HV-Dia]|Rest],Tab,Tab1)
                                 )
                         )
                      );(
                           (Piece = sq; Piece = ar),!,
                           (
                                   (
                                      write(Piece), write(' Selected ! '),nl,
                                      write(Terrain),nl,
                                      Terrain \= m, Terrain \= [c-_],!,
                                      write('---->B'),nl,
                                      place(Tab,E-Piece-Number,X,Y,Tab2),
                                      write('---->A'),nl,
                                      write(pieces(E,En,Rest,Tab2,Tab1)),nl,
                                      pieces(E,En,Rest,Tab2,Tab1)
                                   );(
                                      clearScreen,
                                      write('Mountain Terrain or a Castle located on those coordinates!'),nl,
                                      pieces(E,En,[[Piece-Number-Name-HV-Dia]|Rest],Tab,Tab1)
                                   )
                           )
                      )
                   )
                );(
                     clearScreen,
                     write('No valid coordinates or a piece already there!'),nl,
                     pieces(E,En,[[Piece-Number-Name-HV-Dia]|Rest],Tab,Tab1)
                ).

gameplay(_,_, Turn,[P|_]):-
        % se for uma peça não instanciada
        % criada pelo findall não encontrar peças
        % significa que não existe mais peças para o jogador
        % jogar logo o adeversário ganha
        P = ni-ni,!,write('------->A'),nl,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),abort.

gameplay(T,_, Turn,_):-
        % Se a realeza foi morta
        % o adeversário ganha
        availablePieces(Turn, T, PT),
        \+(member(k-1, PT)),
        \+(member(d-1, PT)),
        \+(member(p-1, PT)),!,write('------->B'),nl,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),abort.

gameplay(T,_, Turn,_):-
        % Se o castelo foi ocupado pelo adeversário
        % o adeversário ganha
        find(T, [c-Turn]-E-_-_, _-_),
        E \= v, E \= Turn, !,write('------->C'),nl,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),abort.

gameplay(T,NT, Turn,PT):-
        turn(Turn,T,NewFinal,P,PT),!,
        (
           (
              P = def,!, fail
           );true
        ),
        processTurn(h, Turn,NewFinal,NT,P,PT).

processTurn(Type, Turn,NewFinal,NT,P,PT):-
        (
           (
               ( % Se terminou
                  P = done;
                  (% ou não existe mais peças para jogar
                     (
                        (
                           P = P2-N
                        );(
                           P = k, P2 = k, N = 1;
                           P = d, P2 = d, N =1;
                           P = p, P2 = p, N =1
                        )
                     ),
                     deleteFormList(P2-N, PT, PT2),
                     PT2 = []
                  )
               ),!,
               NT = NewFinal
           );(
                P = def, !, fail
           );(
               P \= done,!,
               (
                  (
                     P = P2-N
                  );(
                     P = k, P2 = k, N = 1;
                     P = d, P2 = d, N =1;
                     P = p, P2 = p, N =1
                  )
               ),deleteFormList(P2-N, PT, PT2),
               (
                  (
                     Type = h,!,
                     GP =.. [gameplay, NewFinal, NT, Turn, PT2]
                  );(
                     Type = hai,!,
                     GP =.. [gameplayHvAI, NewFinal, NT, Turn, PT2]
                  );(
                     Type = ai,!,
                     GP =.. [gameplayAI, NewFinal, NT, Turn, PT2]
                  )
               ),GP
           )
        ).

gameplay(T):-
                availablePieces(a, T, PA),
                gameplay(T, NT, a, PA),                
                availablePieces(b, NT, PB),
                gameplay(NT, NT2, b, PB),
                gameplay(NT2).
gameplay(_).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%       Human vs AI         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

gameplayHvAI(_,_, Turn,[P|_],_):-
		
        P = ni-ni,!,write('------->A'),nl,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),abort.

gameplayHvAI(T,_, Turn,_,_):-
        availablePieces(Turn, T, PT),
        \+(member(k-1, PT)),
        \+(member(d-1, PT)),
        \+(member(p-1, PT)),!,write('------->B'),nl,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),abort.

gameplayHvAI(T,_, Turn,_,_):-
        find(T, [c-Turn]-E-_-_, _-_),
        E \= v, E \= Turn, !,write('------->C'),nl,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),abort.

gameplayHvAI(T,NT, Turn,PT,Dif):-
        (
           (
              Turn = a,!,
              turn(Turn,T,NewFinal,P,PT),
              (
                 (
                    P = def,!, fail
                 );true
              ),
              processTurn(h, Turn,NewFinal,NT,P,PT)
           );(
              Turn = b,!,
			 ((Dif>0, 
			  turnAI(Turn,T,NT,PT,P-N),
			  deleteFormList(P-N, PT, PT2),
			  Dif2 is Dif-1,
			  gameplayHvAI(NT,NT2, Turn,PT2,Dif2));
			  true)
             
			 % processTurn(hai, Turn,NewFinal,NT,P,PT)
           )
        ).
        

gameplayHvAI(T,Dif):-
        
	availablePieces(a, T, PA),
	gameplay(T, NT, a, PA),
	availablePieces(b, NT, PB),
    gameplayHvAI(NT, NT2, b, PB,Dif),
    gameplayHvAI(NT2,Dif).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%          $AI          %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
count([],0).
count([H|T],N) :- count(T,N1) , N is N1+1.
	

turnAI(Turn,T,T2,PT,P-N):-
        %nl,nl,write('Player'),write(Turn),write(' turn.'),nl,showTab(T),write('Press any key to continue.'),nl,read(GO),
	
	count(PT,NumberL),
	Sum is NumberL+1,
	random(1,Sum,RP),
	choosePiecetomove(PT,P-N,RP),
	bestMove(T,P-N,Turn,1,[],FList),
	makeDecision(T,P-N,Turn,FList,0-0-0-0,[DirD-XD-YD-ScoreD]),
	move(T,XD,YD,Turn,P,N,T2).

choosePiecetomove([PL-NL|Rest],P-N,1):- P=PL,N=NL.
choosePiecetomove([H|Rest],P-N,RP):-
	RPnew is RP-1,
	choosePiecetomove(Rest,P-N,RPnew).

	
makeDecision(T,P-N,Turn,[DirT-XT-YT-ScoreT|Rest],DirI-XI-YI-ScoreI,[DirF-XF-YF-ScoreF]):-
	(ScoreI<ScoreT,
        	(
                   (
                      Rest\=[],makeDecision(T,P-N,Turn,Rest,DirT-XT-YT-ScoreT,[DirF-XF-YF-ScoreF])
                   );(
                     DirF=DirT,XF=XT,YF=YT,ScoreF=ScoreT
                   )
                )
        );
		(ScoreI=ScorteT, random(1,500,RandomN), ((RandomN<250,        	(
                   (
                      Rest\=[],makeDecision(T,P-N,Turn,Rest,DirT-XT-YT-ScoreT,[DirF-XF-YF-ScoreF])
                   );(
                     DirF=DirT,XF=XT,YF=YT,ScoreF=ScoreT
                   )
                ));(RandomN>250,fail)))
		;
		(
             (
                (
                   Rest\=[],
                   makeDecision(T,P-N,Turn,Rest,DirI-XI-YI-ScoreI,[DirF-XF-YF-ScoreF])
                );(
                   DirF=DirI,XF=XI,YF=YI,ScoreF=ScoreI
                )
             )
          ).
	
		
		
		
	
bestMove(_,_-_,_,9,IList,FList):-FList=IList.
bestMove(T,P-N,Turn,Dir,List,FList):-
	movesList(T,Dir,P-N,1,List,Turn,IList),
	NewDir is Dir+1,
	bestMove(T,P-N,Turn,NewDir,IList,FList).
			
			
maxSpaces([[PL-NL-DC-HL-DL]|Rest],P-N,D-H):-
	PL\=P,maxSpaces(Rest,P-N,D-H).
maxSpaces([[PL-NL-DC-HL-DL]|Rest],P-N,D-H):-
	PL=P,NL\=N,maxSpaces(Rest,P-N,D-H).
maxSpaces([[PL-NL-DC-HL-DL]|Rest],P-N,D-H):-
	PL=P,NL=N,D=DL,H=HL.
				
				
searchT(Tab,T-E-P-N,X,Y):- searchTe(Tab,X,Y,T-E-P-N).
searchTe([_|Tab],X,Y,T-E-P-N):-
        Y>1,
        Y2 is Y-1,
        searchTe(Tab,X,Y2,T-E-P-N).
        searchTe([H|_],X,1,T-E-P-N):-
        searchTe2(H,X,T-E-P-N).
	searchTe2([_|Tab],X,T-E-P-N):-
        X>1,
        X2 is X-1,
        searchTe2(Tab,X2,T-E-P-N).
        searchTe2([TL-EL-PL-NL|_],1,T-E-P-N):-T=TL,E=EL,P=PL,N=NL.
				
				
findScore(Tab,Turn,X-Y,Score):-
	searchT(Tab,T-E-P-N,X,Y),			
	((E\=Turn,E\=v,Score=2);(Score=1)).	
		
		
		
movesList(T,Dir,P-N,Spaces,List,Turn,Final):-
    pieceList(PI),
    find(T, _-Turn-P-N, X1-Y1),                     
    maxSpaces(PI,P-N,D-H),
    (   
       (
          % O sq move-se de forma diferente uma casa h ou v e uma diagonal, sempre
          % o que significa que só tem um movimento nesta direcção
		  	
          P = sq,!,
          ((verifyMove(T,P,X1-Y1,Dir,Spaces,X-Y),%write(Spaces-Dir-P-N-X-Y-Turn),nl,nl,write(' f|'),
          findScore(T,Turn,X-Y,Score),
          append(List,[Dir-X-Y-Score],Final))
		  ;
		  Final=List,true
		  )
       );(
          Hnew is H+1,
          Dnew is D+1,
          (
            (
               (Dir=:=2;Dir=:=4;Dir=:=5;Dir=:=7),
               Spaces<Hnew,
               (
                  (
                     verifyMove(T,P,X1-Y1,Dir,Spaces,X-Y),
                     SpacesN is Spaces+1,
                     findScore(T,Turn,X-Y,Score),
                     append(List,[Dir-X-Y-Score],List2),
                     movesList(T,Dir,P-N,SpacesN,List2,Turn,Final)
                  );(
                     SpacesN is Spaces+1,
                     movesList(T,Dir,P-N,SpacesN,List,Turn,Final)
                  )
               )
            );(
               (Dir=:=1;Dir=:=3;Dir=:=6;Dir=:=8),
               Spaces<Dnew,
               (
                  (
                     verifyMove(T,P,X1-Y1,Dir,Spaces,X-Y),
                     SpacesN is Spaces+1,
                     findScore(T,Turn,X-Y,Score),
                     append(List,[Dir-X-Y-Score],List2),
                     movesList(T,Dir,P-N,SpacesN,List2,Turn,Final)
                  );(
                     SpacesN is Spaces+1,
                     movesList(T,Dir,P-N,SpacesN,List,Turn,Final)
                  )
               )
            );Final=List,true
          )
       )
    ).








%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%          Ai vs AI         %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		
gameplayAI(_,_, Turn,[P|_]):-
        P = ni-ni,!,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),showTab(T),abort.

gameplayAI(T,_, Turn,_):-
        availablePieces(Turn, T, PT),
        \+(member(k-1, PT)),
        \+(member(d-1, PT)),
        \+(member(p-1, PT)),!,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),showTab(T),abort.

gameplayAI(T,_, Turn,_):-
        find(T, [c-Turn]-E-_-_, _-_),
        E \= v, E \= Turn, !,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),showTab(T),abort.

gameplayAI(T,NT, Turn,PT):-
	turnAI(Turn,T,NT,PT,P).
        

gameplayAI(T):-
        availablePieces(a, T, PA),
        write('Turn A'),nl,write('Write anything to continue'),nl,read(CONTINUE1),
        showTab(T),nl,
        gameplayAI(T, NT, a, PA),
        availablePieces(b, NT, PB),
        write('Turn B'),nl,write('Write anything to continue'),nl,read(CONTINUE2),
		showTab(NT),nl,
		gameplayAI(NT, NT2, b, PB),
        gameplayAI(NT2).

gameplayAI(_).




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%                           %%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


turn(Turn,T,T2,Pice,PT):-
                showTab(T),
                ((Turn=a,write('Player A: ')); % Se é o turno A
                (Turn=b,write('Player B: '))), % Se é o turno B
                write('Choose Piece to move (P-N/def/done)'),read(Pice),
                ((Pice = def,!,((Turn=b, write('Player A Wins'),nl);       % Se B desiste
                             (Turn=a, write('Player B Wins'),nl)),abort); % Se A desiste
                (Pice = P-N);
                (  % Se as peças são apenas k,p ou d.
                   (Pice = k, P = k, N = 1);
                   (Pice = d, P = d, N = 1);
                   (Pice = p, P = p, N = 1);
                   (P = error, N = 1)
                );( % Se terminou o turno T mantén-se
                     Pice = done,
                     T2 = T
                )),(
                   (   % Se terminou o turno sai fora
                      Pice = done,!,
                      T2 = T
                   );( % se jogada é possivel
					  P \= error,
                      member(P-N, PT),
					 (
					 (P=ar,nl,write('Shoot or Move?(\'move\' or \'shoot\')'),read(OPTION),
					  (
					   (OPTION=move,chooseDirection(T,X,Y,Turn-P-N,_),!,move(T,X,Y,Turn,P,N,T2));
					   (OPTION=shoot,chooseDirection(T,X,Y,Turn-P-N,_),!,move(T,X,Y,v,v,1,T2))
					   )
					  );					  
                      (chooseDirection(T,X,Y,Turn-P-N,_),!,move(T,X,Y,Turn,P,N,T2))%,verifyAr(T3, Turn, X-Y, T2))
					  )					  
                   );( % senão jogada inválida
                        nl,write('Unavailable Move. Try again.'),nl,nl, turn(Turn, T,T2,_,PT)
                   )
                ).

verifyAr(T, Turn, X-Y, T2):-
        verifyArDir(T, 3, Turn, X-Y, X-Y, u, T3),
        verifyArDir(T3, 3, Turn, X-Y, X-Y, d, T4),
        verifyArDir(T4, 3, Turn, X-Y, X-Y, r, T5),
        verifyArDir(T5, 3, Turn, X-Y, X-Y, l, T6),
		
        verifyArDir(T6, 3, Turn, X-Y, X-Y, ru, T7),
        verifyArDir(T7, 3, Turn, X-Y, X-Y, lu, T8),
        verifyArDir(T8, 3, Turn, X-Y, X-Y, rd, T9),
        verifyArDir(T9, 3, Turn, X-Y, X-Y, ld, T2).

verifyArDir(T, 0, _, _, _, _, T):-!.
verifyArDir(T, N, Turn, X-Y, X1-Y1, Dir, T2):-
        N > 0,
        (
            N2 is N - 1,
            (
               (
                  Dir = u,!,
                  X2 = X1,
                  Y2 is Y1 - 1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               );(
                  Dir = d,!,
                  X2 = X1,
                  Y2 is Y1 + 1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               );(
                  Dir = r,!,
                  X2 is X1 + 1,
                  Y2 = Y1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               );(
                  Dir = l,!,
                  X2 is X1 - 1,
                  Y2 = Y1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               );(
                  Dir = lu,!,
                  X2 is X1 - 1,
                  Y2 is Y1 - 1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               );(
                  Dir = ru,!,
                  X2 is X1 + 1,
                  Y2 is Y1 - 1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               );(
                  Dir = ld,!,
                  X2 is X1 - 1,
                  Y2 is Y1 + 1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               );(
                  Dir = rd,!,
                  X2 is X1 + 1,
                  Y2 is Y1 + 1,
                  verifyAr(T, Turn, X-Y, X2-Y2, T3)
               )
            ),
            verifyArDir(T3, N2, Turn, X-Y, X2-Y2, Dir, T2)
        ).

verifyAr(T, Turn, X-Y, X1-Y1, T2):-
        sizeTabH(H),
        sizeTabW(W),
        X1 =< W, X1 >=1,
        Y1 =< H, Y1 >=1,
        (
           (
              %write(X1-Y1),nl,
              find(T, _-E1-P1-_, X1-Y1),
              E1 \= Turn, P1 = ar,!,
              place(T, v-v-1, X,Y, T2)
           );(
                T2 = T
           )
        ).

verifyTerrain(_, _, _-_, _, 0).
verifyTerrain(T, Te, X-Y, Direction, Spaces):-
        Spaces >= 1,
        (
           (
              Direction = 1,!,
              X1 is X - 1,
              Y1 is Y - 1,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           );(
              Direction = 2,!,
              X1 = X,
              Y1 is Y - 1,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           );(
              Direction = 3,!,
              X1 is X + 1,
              Y1 is Y - 1,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           );(
              Direction = 4,!,
              X1 is X - 1,
              Y1 = Y,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           );(
              Direction = 5,!,
              X1 is X + 1,
              Y1 = Y,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           );(
              Direction = 6,!,
              X1 is X - 1,
              Y1 is Y + 1,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           );(
              Direction = 7,!,
              X1 = X,
              Y1 is Y + 1,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           );(
              Direction = 8,!,
              X1 is X + 1,
              Y1 is Y + 1,
              find(T, Te2-P-_-_, X1-Y1),
              Te2 \= Te,
              S is Spaces - 1
           )              
        ),((P = v,verifyTerrain(T, Te, X1-Y1, Direction, S));(S=0,verifyTerrain(T, Te, X1-Y1, Direction, S))).

verifyDest(T, X-Y, Spaces, XF-YF):-

        (
           Spaces = 1,!,
           find(T, Te-E-_-_, X-Y),
           find(T, Te2-E2-_-_, XF-YF),
           E \= E2,
           (
              (
                 Te = [c-_],!,
                 Te2 = [g-_]
              );(
                 Te2 = [c-_],!,
                 Te = [g-_]
              );true
           )
        );(
             Spaces > 1,!,
             find(T, _-E-_-_, X-Y),
             find(T, Te2-E2-_-_, XF-YF),
             Te2 \= [c-_], E \= E2
        ).

calcDest(X-Y, Direction, Spaces, XF-YF):-
        (
           Direction = 1,!,
           XF is X - Spaces,
           YF is Y - Spaces
        );(
           Direction = 2,!,
           XF = X,
           YF is Y - Spaces
        );(
           Direction = 3,!,
           XF is X + Spaces,
           YF is Y - Spaces
        );(
           Direction = 4,!,
           XF is X - Spaces,
           YF = Y
        );(
           Direction = 5,!,
           XF is X + Spaces,
           YF = Y
        );(
           Direction = 6,!,
           XF is X - Spaces,
           YF is Y + Spaces
        );(
           Direction = 7,!,
           XF = X,
           YF is Y + Spaces
        );(
           Direction = 8,!,
           XF is X + Spaces,
           YF is Y + Spaces
        ).

verifyMove(T, P, X-Y, Direction, Spaces, XF-YF):-
        (
		   
           P = sq,!,
           (
              (
                 Direction = 1,!,
                 X1 is X,
                 Y1 is Y - 1,
                 X2 is X - 1,
                 Y2 is Y - 2,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              );(
                 Direction = 2,!,
                 X1 is X,
                 Y1 is Y - 1,
                 X2 is X + 1,
                 Y2 is Y - 2,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              );(
                 Direction = 3,!,
                 X1 is X - 1,
                 Y1 is Y,
                 X2 is X - 2,
                 Y2 is Y - 1,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              );(
                 Direction = 4,!,
                 X1 is X + 1,
                 Y1 is Y,
                 X2 is X + 2,
                 Y2 is Y - 1,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              );(
                 Direction = 5,!,
                 X1 is X - 1,
                 Y1 is Y,
                 X2 is X - 2,
                 Y2 is Y + 1,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              );(
                 Direction = 6,!,
                 X1 is X + 1,
                 Y1 is Y,
                 X2 is X + 2,
                 Y2 is Y + 1,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              );(
                 Direction = 6,!,
                 X1 is X,
                 Y1 is Y + 1,
                 X2 is X - 1,
                 Y2 is Y + 2,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              );(
                 Direction = 7,!,
                 X1 is X,
                 Y1 is Y + 1,
                 X2 is X + 1,
                 Y2 is Y + 2,
                 find(T, Te-_-_-_, X1-Y1),
                 find(T, Te2-_-_-_, X2-Y2),
                 Te \= m, Te \= [c-_],
                 Te2 \= m, Te2 \= [c-_]
              )
           ),
           XF = X2, YF = Y2,
           verifyDest(T, X-Y, Spaces, XF-YF)
        );(
             (P = ki; P = d; P = p),!,
             calcDest(X-Y, Direction, Spaces, XF-YF),
             Spaces2 is Spaces - 1,
             verifyTerrain(T, m, X-Y, Direction, Spaces2),
             verifyTerrain(T, r, X-Y, Direction,Spaces2),
             verifyTerrain(T, [c-_], X-Y, Direction, Spaces2),
             find(T, Te2-_-_-_, XF-YF),
             Te2 \= m, Te2 \= r,
             verifyDest(T, X-Y, Spaces, XF-YF)
        );(
             P = ar,!,
             calcDest(X-Y, Direction, Spaces, XF-YF),
             Spaces2 is Spaces - 1,
             verifyTerrain(T, m, X-Y, Direction, Spaces2),
             verifyTerrain(T, [c-_], X-Y, Direction, Spaces2),
             find(T, Te2-_-_-_, XF-YF),
             Te2 \= m, Te2 \= [c-_],
             verifyDest(T, X-Y, Spaces, XF-YF)
        );(
             (P = k; P = se; P = pi),!,             
             calcDest(X-Y, Direction, Spaces, XF-YF),
             Spaces2 is Spaces - 1,
             verifyTerrain(T, m, X-Y, Direction, Spaces2),
             verifyTerrain(T, [c-_], X-Y, Direction, Spaces2),
             find(T, Te2-_-_-_, XF-YF),
             Te2 \= m,
             verifyDest(T, X-Y, Spaces, XF-YF)
        ).
                
                                
chooseDirection(T,X,Y,E-P-N,Direction):-
                        (
                           P = sq,!,
                           write('  1  2'),nl,
                           write('   \\/'),nl,
                           write('3   |    4'),nl,
                           write(' >- sq -<'),nl,
                           write('5   |    6'),nl,
                           write('    /\\'),nl,
                           write('   7  8'),nl,
                           write('Choose direction: '),read(Direction),
                           find(T, _-E-P-N, X1-Y1),
                           verifyMove(T, P, X1-Y1, Direction, _, X-Y)
                        );(
                             write(' 1  2  3 '), nl,
                             write('  \\ | /  '), nl,
                             (
                                (
                                   (
                                      P = k;
                                      P = d;
                                      P = p
                                   ),!,
                                     write('4 - '), write(P),write(' - 5'),nl
                                );(
                                     write('4 - '), write(P),write('- 5'),nl
                                )
                             ),
                             write('  / | \\  '), nl,
                             write(' 6  7  8 '), nl,
                             write('Choose direction: '),
                             read(Direction),
                             write('How many?'),
                             read(Spaces),
                             find(T,_-E-P-N,X1-Y1),
                             verifyMove(T, P, X1-Y1, Direction, Spaces, X-Y)
                          ).