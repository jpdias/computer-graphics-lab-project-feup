%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% main.pro - Programa principal                                            %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Representa o ficheiro que liga a lógica e a estrutura de dados.          %
%                                                                          %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% a usar o modulo especificado em 'modules/tab.pro'
:- use_module(library(random)).
:- use_module(library(clpfd)).
:- use_module('modules/tab.pro').
:- use_module('modules/validation.pro').

user:runtime_entry(start) :- run.

run:- clearScreen, menuModeSelection.

menuModeSelection:-
        write('Feudal Game'),nl,
        write('###########'),nl,
        nl,
        write('Select mode: '),nl,
        write('    1 - Human vs Human'),nl,
        write('    2 - Human vs AI'),nl,
        write('    3 - AI vs AI'),nl,
        nl,
        write('Choice: '), read(C),
        (
           (
              C = 1,!,
              menuChooseMap(T, Map),
              menuStrategies(a, Map, T, T2),
              menuStrategies(b, Map, T2, T3),
              gameplay(T3)
           );(
              C = 2,!,
              write('Difficulty (1-3):'),
              read(Input),
              (
                 (Input<2,Dif=1);(Input=2,Dif=2);(Input>2,Dif=3)
              ),
              clearScreen,
              random(1,4,Map),
              chooseMap(Map, T),
              menuStrategies(a, Map, T, T2),
              random(1,2,Startegy),
              chooseStrategy(Startegy, b, Map, T2, T3),
              gameplayHvAI(T3,Dif)
           );(
              C = 3,!,
              clearScreen,
              random(1,4,Map),
              chooseMap(Map, T),
              random(1,2,Startegy),
              chooseStrategy(Startegy, a, Map, T, T2),
              random(1,2,Startegy2),
              chooseStrategy(Startegy2, b, Map, T2, T3),
              write('Initial Board:'),nl,
              showTab(T3),
              gameplayAI(T3)
           );(
              clearScreen,
              write('Not valid choice!'), nl,
              menuModeSelection
           )
        ).

menuStrategies(Turn, Map, T, Tab):-
        clearScreen,
        write('Player '),
        (
           (
              Turn = a,
              write('A'),nl
           );(
              Turn = b,
              write('B'),nl
           )
        ),
        write('########'),nl,
        nl,
        write('Select Strategies:'),nl,
        write('    1 - Strategy A'),nl,
        write('    2 - Strategy B'),nl,
        write('    3 - Custom Strategy'),nl,
        nl,
        write('Choice (select a or b for more info): '), read(C),
        (
           (
              C = a,!,
              clearScreen,
              write('    * 4 Pikemen and 2 Sergeants, group in the center of'), nl,
              write('      board, are to invade enemy territory.'), nl,
              nl,
              write('    * Archer is positioned between Castle and center of'), nl,
              write('      board as backup for attack and possible defensive'), nl,
              write('      maneuvers.'), nl,
              nl,
              write('    * Mounted man, positioned at corners of board, are '), nl,
              write('      also ready to attack or, if necessary, to defend'), nl,
              write('      the Castle.'), nl,
              nl,
              write('    * King and Squire are kept near Castle strictly for'), nl,
              write('      defensive purposes; these pieces work best together'), nl,
              write('      because of their restrictive moves.'), nl,
              nl,
              write('    * Castle placement is week; defense will be difficult'), nl,
              write('      as there are five possible entrances to Green.'), nl,
              write('      because of their restrictive moves.'), nl,
              nl,
              write('Type anything to continue...'),read(_),
              menuStrategies(Turn, Map, T, Tab)
           );(
              C = b,!,
              clearScreen,
              write('    * Castle placement allows only three entraces to Green'), nl,
              write('      one entrace is over rough terrain (forbidden to'), nl,
              write('      mounted men).'), nl,
              nl,
              write('    * Archer, positioned on Green, provides additional'), nl,
              write('      protection for Castle.'), nl,
              nl,
              write('    * King and Squire (pieces which work best together) are'), nl,
              write('      placed near Castle for further defensive purposes.'), nl,
              nl,
              write('    * Certain mounted men as well as 2 Pikemen and Sergeants'), nl,
              write('      are placed in the center of the board, so they may'), nl,
              write('      either defend or attack.'), nl,
              nl,
              write('Type anything to continue...'),read(_),
              menuStrategies(Turn, Map, T, Tab)
           );(
                chooseStrategy(C, Turn, Map, T, Tab),!
           );(
              write('Not a valid choice!'), nl,
              write('Type anything to continue...'),read(_),
              menuStrategies(Turn, Map, T, Tab)
           )
        ).

chooseStrategy(Strategy, Turn, Map, T, Tab):-
        sizePTabH(H),
        divideTab(T,H,T1,T2),
        (
           (
              Strategy = 1,!,
              (
                 (
                    (isClassicMap(Map);isEmptyMap(Map)),!,
                    positionClassicMapA(P),
                    placeOnMap(P, T, Turn, Tab)
                 );(
                    (isMountainMap(Map);isRoughtTerrainMap(Map)),!,
                    positionMapA(P),
                    placeOnMap(P, T, Turn, Tab)
                 )
              )
           );(
              Strategy = 2,!,
              (
                 (
                    (isClassicMap(Map);isEmptyMap(Map)),!,
                    positionClassicMapB(P),
                    placeOnMap(P, T, Turn, Tab)
                 );(
                    (isMountainMap(Map);isRoughtTerrainMap(Map)),!,
                    positionMapB(P),
                    placeOnMap(P, T, Turn, Tab)
                 )
              )
           );(
              Strategy = 3,!,
              (
                 (
                    Turn = a,
                    placePieceTurn(Turn, T1, NT),
                    append(NT, T2, Tab)
                 );(
                    Turn = b,
                    placePieceTurn(Turn, T2, NT),
                    append(T1, NT, Tab)
                 )
              )
           )
        ).

chooseMap(Map, Tab):-
        (
           (
              isClassicMap(Map),!,
              initBlankTab(T),
              sizePTabH(H),
              divideTab(T,H,T1,_),
              mapClassicList(L),
              putTerrainList(T1, L, T2),
              reverse(T2, T3),
              append(T2, T3, Tab)              
           );(
              isMountainMap(Map),!,
              initBlankTab(T),
              sizePTabH(H),
              divideTab(T,H,T1,_),
              mapMountainList(L),
              putTerrainList(T1, L, T2),
              reverse(T2, T3),
              append(T2, T3, Tab)              
           );(
              isRoughtTerrainMap(Map),!,
              initBlankTab(T),
              sizePTabH(H),
              divideTab(T,H,T1,_),
              mapMountainList(L),
              putTerrainList(T1, L, T2),
              reverse(T2, T3),
              append(T2, T3, Tab)              
           );(
              isEmptyMap(Map),!,
              initBlankTab(Tab)            
           )
        ).

menuChooseMap(Tab, Map):-
        clearScreen,
        write('Player B'),nl,
        write('########'),nl,
        nl,
        write('Select Map: '),nl,
        write('    1 - Classic        3 - Rough Terrain'),nl,
        write('    2 - Mountain       4 - Empty Map'),nl,
        nl,
        write('Choice: '), read(C),
        chooseMap(C, Tab),
        Map = C.