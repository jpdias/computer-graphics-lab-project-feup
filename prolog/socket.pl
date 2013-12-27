%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 Sockets                   %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-use_module(library(sockets)).
:- use_module('validation.pro').
:- use_module('tab.pro').
:- use_module('main.pro').
port(60070).

% launch me in sockets mode
server:-
	port(Port),
	socket_server_open(Port, Socket),
	socket_server_accept(Socket, _Client, Stream, [type(text)]),
	write('Accepted connection'), nl,
	run2(Tab),
	serverLoop(Stream,Tab,a),
	socket_server_close(Socket).

% wait for commands
serverLoop(Stream,Tab,Turn) :-
	repeat,
	read(Stream, ClientMsg),
	write('Received: '), write(ClientMsg), nl,
	%%%%parse_input(ClientMsg, MyReply),
	(
	(command(ClientMsg,Tab,Turn,T2,NextTurn)
	,write('hey'),Reply = true,format(Stream, '~q~n', [Reply]))
	;
	(NextTurn=Turn,T2=Tab,Reply = false,format(Stream, '~q~n', [Reply]))
	),
	write('Wrote: '),write(Reply), nl,flush_output(Stream),(ClientMsg==quit;serverLoop(Stream,T2,NextTurn)).


	%% Move Piece
	command(Cmd-P-E-N-Direction-Spaces,T,Turn,T2,NextTurn):-
		Cmd=movepiece,socketVerifyMove(T,P-E-N-Direction-Spaces,Turn,T2,NextTurn).
	
	%% Checks Turn
	command(Cmd-Isturn,T,Turn,T2,NextTurn):-
		 Cmd=checkturn,Turn=Isturn.
	
	%% Changes Turn
	command(Cmd,T,Turn,T2,NextTurn):-
		 Cmd=changeturn,((Turn=a,NextTurn=b) ; (Turn=b,NextTurn=a)).
	
	%% Checks if someone won
	isOver(T,Reply):-
		isRoyaltydead(T,a),Reply=bwins.
		
	
	isRoyaltydead(T,Turn):-	
	  availablePieces(Turn, T, PT),
        \+(member(k-1, PT)),
        \+(member(d-1, PT)),
        \+(member(p-1, PT)),!,write('------->B'),nl,
        (
                (Turn=b, write('Player A Wins'),nl);
                (Turn=a, write('Player B Wins'),nl)
        ),abort.
		
	
	socketVerifyMove(T,P-E-N-Direction-Spaces,Turn,T2,NextTurn):-
		Turn=E,
		find(T, _-E-P-N, X1-Y1),
		verifyMove(T, P, X1-Y1, Direction, Spaces, XF-YF),
		move(T,XF,YF,E,P,N,T2),
		NextTurn=Turn.
	