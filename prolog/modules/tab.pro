%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% tab.pro - Representação e funções auxiliares                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
% Neste ficheiro encontrão-se as intruções de definição e visualização do  %
% tabuleiro do jogo. Enconta-se também predicados auxiliares na busca e    %
% colocação de peças(sem verificação).                                     %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%:- use_module('moves.pro').

% Definicao do modulo 'tabRepresentation', e sua interface publica
:- module(tabRepresentation, [
      sizePTabH/1,
      sizeTabH/1,
      sizeTabW/1,
      initBlankTab/1,
      showTab/1,
      clearScreen/0,
      
      isClassicMap/1,
      isMountainMap/1,
      isRoughtTerrainMap/1,
      isEmptyMap/1,
      positionClassicMapA/1,
      positionClassicMapB/1,
      positionMapA/1,
      positionMapB/1,
      placeOnMap/4,
      mapClassicList/1,
      mapMountainList/1,
      mapRoughtTerrainList/1,
      putTerrainList/3,
      
      availablePieces/3,
      allPieces/1,
      pieceList/1,
      
      move/7,
      find/3,
      findP/4,
      findT/4,
      put/7,
      place/5,
      
      deleteFormList/3,
      reverse/2,
      divideTab/4,
      
      terrain/2,
      team/2,
      piece/2,
      number/2
]).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Procura todas as peças da equipa Turn e coloca-as na lista List          %
% É usado em gameplay para detectar as peças disponíveis para o jogador    %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
% availablePieces(+Turn, +Tab, -List).                                      %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
availablePieces(Turn, Tab, List):-
        findall(P-N, find(Tab, _-Turn-P-N, _-_), List).

allPieces([
    k-1, p-1, d-1,
    ki-1, ki-2,
    se-1, se-2,
    sq-1, ar-1,
    pi-1, pi-2, pi-3, pi-4
]).

pieceList([[k-1-'King'-3-3],[p-1-'Prince'-24-24],[d-1-'Duke'-24-24],[ki-1-'Kight 1'-24-24],[ki-2-'Kight 2'-24-24],[se-1-'Sergeant 1'-2-13],
                        [se-2-'Sergeant 2'-2-13],[sq-1-'Squire'-'ERROR'-'ERROR'],[ar-1-'Archer'-4-4],[pi-1-'Pikeman 1'-13-2],[pi-2-'Pikeman 2'-13-2],[pi-3-'Pikeman 3'-13-2],
                        [pi-4-'Pikeman 4'-13-2]]).

placeOnMap(P, T, Turn, NT):-
        atom(Turn),
        (
           (
              Turn = b,!,
              reverse(T, T2)
           );(
              T2 = T
           )
        ),placeOnMap(T2, Turn, P, T3),
        (
           (
              Turn = b,!,
              reverse(T3, NT)
           );(
              NT = T3
           )
        ).

placeOnMap(NT, _, [], NT).
placeOnMap(T, Turn, [P-N-X-Y|R], NT):-
        P \= c, P \= g,
        place(T,Turn-P-N,X,Y,T2),
        placeOnMap(T2, Turn, R, NT).
placeOnMap(T, Turn, [P-_-X-Y|R], NT):-
        put(T,[P-Turn]-v-v-1,[],[],X,Y,T2),
        placeOnMap(T2, Turn, R, NT).

positionClassicMapA([
    c-_-13-2, g-_-13-3,
    k-1-12-4, p-1-1-2, d-1-24-1,
    ki-1-2-8, ki-2-24-8,
    se-1-13-10, se-2-14-10,
    sq-1-14-4, ar-1-13-7,
    pi-1-11-10, pi-2-12-10, pi-3-15-10, pi-4-16-10
]).

positionClassicMapB([
    c-_-15-5, g-_-15-6,
    k-1-17-7, p-1-6-6, d-1-22-6,
    ki-1-10-9, ki-2-17-9,
    se-1-13-9, se-2-14-9,
    sq-1-16-7, ar-1-15-6,
    pi-1-12-9, pi-2-15-9, pi-3-12-4, pi-4-18-4
]).

positionMapA([
    c-_-16-2, g-_-17-2,
    k-1-18-3, p-1-1-1, d-1-24-1,
    ki-1-1-10, ki-2-24-10,
    se-1-16-9, se-2-17-9,
    sq-1-17-4, ar-1-16-7,
    pi-1-14-9, pi-2-15-9, pi-3-18-9, pi-4-19-9
]).

positionMapB([
    c-_-22-4, g-_-22-5,
    k-1-21-7, p-1-2-4, d-1-17-5,
    ki-1-15-9, ki-2-24-9,
    se-1-20-9, se-2-21-9,
    sq-1-22-7, ar-1-22-5,
    pi-1-19-4, pi-2-24-5, pi-3-19-9, pi-4-22-9
]).

isClassicMap(1).
mapClassicList([
           m-1-1, m-1-9, m-1-10, m-4-1, r-4-5, r-5-8, r-6-9, m-10-4, m-10-5, m-11-7, m-11-8,
           m-14-5, r-14-6, m-15-7, m-15-8, m-16-5, m-16-6, r-18-8, r-18-9, r-19-4, r-19-5, r-19-8,
           m-19-9, r-20-4, r-20-5, m-20-8, r-23-6
]).

isMountainMap(2).
mapMountainList([
           m-4-5, m-4-6, m-5-7, m-6-8, m-7-2, m-9-5, m-9-10, m-10-5, m-10-11, m-10-12,
           m-12-2, m-12-7, m-13-10, m-14-6, m-16-3, m-16-4, m-16-10, m-18-6, m-19-7,
           m-21-5, m-21-4, m-21-11, m-22-4, m-22-6, m-23-5
]).

isRoughtTerrainMap(3).
mapRoughtTerrainList([
           r-4-5, r-4-6, r-5-7, r-6-8, r-7-2, r-9-5, r-9-10, r-10-5, r-10-11, r-10-12,
           r-12-2, r-12-7, r-13-10, r-14-6, r-16-3, r-16-4, r-16-10, r-18-6, r-19-7,
           r-21-5, m-21-4, r-21-11, r-22-4, r-22-6, r-23-5
]).

isEmptyMap(4).

putTerrainList(Tab, [], Tab).
putTerrainList(Tab, [T-X-Y|R], NT):-
        put(Tab,T-v-v-1,[],[],X,Y,NT2),
        putTerrainList(NT2, R, NT).

clearScreen:-
        clearScreen(25).
clearScreen(N):- N = 0.
clearScreen(N):-
        N \= 0,
        N2 is N -1,
        nl,
        clearScreen(N2).
                
divideTab(L,0,[],L).
divideTab([X|Xs],N,[X|Ys],Zs) :- 
        N > 0, 
        N1 is N - 1, 
        divideTab(Xs,N1,Ys,Zs).
                  
                        
%%%%%%%%%%%%%%%%%%%%%%
%        Move        %
%%%%%%%%%%%%%%%%%%%%%%  
move(T,X,Y,E,P,N,T2) :- 
                find(T,_-E-P-N,X2-Y2),
                write('From: '),write(X2-Y2),write(' to '),write(X-Y),nl,
                place(T,v-v-1,X2,Y2,New),               
                place(New,E-P-N,X,Y,T2).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Criar Tabuleiro                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
% initBlankTab(+Tab).                                                      %
%                                                                          %
% sizeTabW(-W).                                                            %
% sizeTabH(-H).                                                            %
% sizePTabH(-PH).                                                          %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

sizeTabW(24).
sizeTabH(24).
sizePTabH(X):-
        sizeTabH(K),
        X is round(K / 2).

initBlankTab(T) :-
             sizeTabW(W),
             sizeTabH(H),
             criaTabuleiro(W,H,T),
             instancia(T,n-v-v-1).
                        

criaTabuleiro(NL,NC,Tabuleiro) :-
         length(Tabuleiro,NL),
         criaColunas(NC,Tabuleiro).
criaColunas(NC,[Linha1|OutrasLinhas]) :-
         length(Linha1,NC),
         criaColunas(NC,OutrasLinhas).
criaColunas(_,[]).


instancia([Linha1|OutrasLinhas],X) :-
         instanciaLinha(Linha1,X),
         instancia(OutrasLinhas,X).
instancia([],_).
instanciaLinha([X|T],X) :-
         instanciaLinha(T,X).
instanciaLinha([],_).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Mostra Tabuleiro                                                         %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
% showTab(+Tab).                                                           %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

showSeparators(0).
showSeparators(N):-
        N > 0,
        N2 is N - 1,
        showSeparators(N2),
        write('----------+').

showTab([]):- write('+'),
              sizeTabW(W),
              showSeparators(W),nl.

showTab([X|L]):- write('+'),
                 sizeTabW(W),
                 showSeparators(W),nl,
                 showLine(X), showTab(L).

showLine([]):- write('|'),nl.

showLine([Terr-Team-Piece-Number|L]):-
        % Se Team unifica com a
        (Team = a, (
                     Terr = n, write('|    a');      % se terreno n
                     Terr = m, write('|   ^a');      % senão se terreno m
                     Terr = r, write('|   ~a');      % senão se terreno r
                     Terr = [c-a], write('| Ca a');  % senão se terreno é o Castelo da equipa A
                     Terr = [c-b], write('| Cb a');  % senão se terreno é o Castelo da equipa B
                     Terr = [g-a], write('| Ga a');  % senão se terreno é o Green da equipa A
                     Terr = [g-b], write('| Gb a')   % senão se terreno é o Green da equipa B
                  );
         % Se Team unifica com b
         Team = b, (
                     Terr = n, write('|    b');      % se terreno n
                     Terr = m, write('|   ^b');      % senão se terreno m
                     Terr = r, write('|   ~b');      % senão se terreno r
                     Terr = [c-a], write('| Ca b');  % senão se terreno é o Castelo da equipa A
                     Terr = [c-b], write('| Cb b');  % senão se terreno é o Castelo da equipa B
                     Terr = [g-a], write('| Ga b');  % senão se terreno é o Green da equipa A
                     Terr = [g-b], write('| Gb b')   % senão se terreno é o Green da equipa B
                  );
         % Se Team unifica com c
         Team = v, (
                     Terr = n, write('|     ');      % se terreno n
                     Terr = m, write('| ^^^^');      % senão se terreno m
                     Terr = r, write('| ~~~~');      % senão se terreno r
                     Terr = [c-a], write('|  Ca ');  % senão se terreno é o Castelo da equipa A
                     Terr = [c-b], write('|  Cb ');  % senão se terreno é o Castelo da equipa B
                     Terr = [g-a], write('|  Ga ');  % senão se terreno é o Green da equipa A
                     Terr = [g-b], write('|  Gb ')   % senão se terreno é o Green da equipa B
                   )
        ),
        (
           (Piece = k, write(' K ')); % se peça k
           (Piece = p, write(' P ')); % senão se peça p
           (Piece = d, write(' D ')); % senão se peça d
           
           (Piece = ki, write(' Ki')); % senão se peça ki
           (Piece = se, write(' Se')); % senão se peça se
           (Piece = sq, write(' Sq')); % senão se peça sq
           (Piece = ar, write(' Ar')); % senão se peça ar
           (Piece = pi, write(' Pi')); % senão se peça pi
           
           (
              Piece = v,
              (
                 (Terr = m,write('^^^'));
                 (Terr = r,write('~~~'));
                 (write('   '))
              )
           )
        ),
        (
           Number > 1, write(Number), write(' ');
           write('  ')
        ),
        showLine(L).


%%%%%%%%%%%%%%%%%%%%%%%
%  Find PieceLocation %
%%%%%%%%%%%%%%%%%%%%%%%
findP(Tab,E-P-N,X,Y):- findPL(Tab,E-P-N,X,Y,1,1).

findPL([H|Tab],E-P-N,X,Y,X2,Y2):-
                        sizeTabH(K),
                        K2 is K + 1,
                        Y2<K2,
                        findPL2(H,E-P-N,X,Y,X2,Y2),
                        Y3 is Y2+1,
                        findPL(Tab,E-P-N,X,Y,1,Y3).
                        
findPL([],_-_-_,_,_,_,K):-
        sizeTabH(K2),
        K3 is K2 + 1,
        K = K3.
                        
findPL2([H|Tab],E-P-N,X,Y,X2,Y3):-
                        sizeTabW(K),
                        X2<K,
                        H \= _-E-P-N,
                        X3 is X2+1,
                        findPL2(Tab,E-P-N,X,Y,X3,Y3).   
                        
findPL2([H|_],E-P-N,X,Y,X2,Y3):-
                        
                        H=_-E-P-N,
                        X is X2,
                        Y is Y3.
                        
findPL2([_|_],_-_-_,_,_,X2,_):-
                        sizeTabW(K),
                        X2=K.
                        
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                      


        
%%%%%%%%%%%%%%%%%%%%%%
%    Find Terrain    %
%%%%%%%%%%%%%%%%%%%%%%
findT(Tab,Terrain,X,Y):- findTe(Tab,X,Y,Terrain).

findTe([_|Tab],X,Y,Terrain):-
                        Y>1,
                        Y2 is Y-1,
                        findTe(Tab,X,Y2,Terrain).
findTe([H|_],X,1,Terrain):-
                        findTe2(H,X,Terrain).
findTe2([_|Tab],X,Terrain):-
                        X>1,
                        X2 is X-1,
                        findTe2(Tab,X2,Terrain).
findTe2([T-_-_-_|_],1,Terrain):-
                                        Terrain=T.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%                      

%%%%%%%%%%%%%%%%%%%%%%
%        Put         %
%%%%%%%%%%%%%%%%%%%%%%  

put([H|Tab],T-E-P-N,Var,Var2,X,Y,New2):-
                        Y>1,
                        append(Var,[H],Z),
                        Y2 is Y-1,
                        put(Tab,T-E-P-N,Z,Var2,X,Y2,New2).
put([H|Tab],T-E-P-N,Z,Var2,X,1,New2):-
                        put2(H,T-E-P-N,X,Var2,G),
                        append(Z,[G],New),
                        append(New,Tab,New2).
                                                
put2([H|Tab],T-E-P-N,X,Var2,G):-
                        X>1,
                        append(Var2,[H],K),
                        X2 is X-1,
                        put2(Tab,T-E-P-N,X2,K,G).

put2([I|Tab],T-E-P-N,1,K,G):-
                        append([T-E-P-N],Tab,Z),
                        append(K,Z,G).

                
%%%%%%%%%%%%%%%%%%%%%%
%        Place       % 
%%%%%%%%%%%%%%%%%%%%%%  
place(Tab,E-P-N,X,Y,NewTab) :-
        findT(Tab,T,X,Y),
        put(Tab,T-E-P-N,[],[],X,Y,NewTab).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Remove um elemento de uma lista caso este não existe retorna a lista     %
% igual.                                                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
% deleteFormList(+Elem, +List, -List2).                                    %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

deleteFormList(_, [], []).
deleteFormList(E, [E|X], NL):-
        deleteFormList(E, X, NL).
deleteFormList(E, [S|X], [S|NL]):-
        E \= S,
        deleteFormList(E, X, NL).

reverse(L, L2):-
        reverse(L, [], L2).
reverse([X|Y],Z,W) :- reverse(Y,[X|Z],W).
reverse([],X,X).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Procura Peça                                                             %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                          %
% find(+Tab, +Pice, -X-Y).                                                 %
%                                                                          %
% terrain(+Pice, -T)                                                       %
% team(+Pice, -T)                                                          %
% piece(+Pice, -P)                                                         %
% number(+Pice, -N)                                                        %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

terrain(T-_-_-_, T).
team(_-T-_-_, T).
piece(_-_-P-_, P).
number(_-_-_-N, N).

find(Tab, T-E-P-N, Y-X):-
        find(Tab, T-E-P-N, X-Y2, 0),
        Y is Y2 + 2.

find([], _, _, _):-!,fail.
find([L|_], T-E-P-N, X-Y, X2):-
        X is X2+1,
        findL(L, T-E-P-N, Y).

find([_|Tab], T-E-P-N, X-Y, X2):-
        X3 is X2+1,
        find(Tab, T-E-P-N, X-Y, X3).

findL(Line, T-E-P-N, Y):-
        findL(Line, T-E-P-N, Y, 0).

%findL([], _, _, _):-!,fail.
findL([T-E-P-N|_], T-E-P-N, Y, Y2):-Y is Y2 - 1.
findL([_-_-_-_|Line], T-E-P-N, Y, Y1):-
        Y2 is Y1 + 1,
        findL(Line, T-E-P-N, Y, Y2).
