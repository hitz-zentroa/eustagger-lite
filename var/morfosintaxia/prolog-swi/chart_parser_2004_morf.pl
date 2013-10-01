% begiratuta built_in predicates atalean, hash_term

%----------------------------------------------------------------------------
%
%	PATR in Prolog:	operators.p
%	
%	Author:		Robert Dale (R.Dale@uk.ac.edinburgh)
%	Revisions:	Shona Douglas (S.Douglas@uk.ac.edinburgh) 
%	Date:		Tuesday 3rd September 1991
%----------------------------------------------------------------------------
%
%	Operators
%
%----------------------------------------------------------------------------

% Path constructor:  this is left-associative:  i.e., a/b/c = (a/b)/c.

:- op(400,  yfx, /).    

% Equality operator for use in constraints:

:- op(500,  xfx, <=>).

% Feature-value pair separator:

:- op(50,   xfx, :).

% Separator for left and right hand sides of grammar rules:

:- op(900, xfx, --->). 

% Separator for rule body and constraints (can be read as "such that"):

:- op(800,  xfx, @).    

% kateaketa adierazteko eragilea

:- op(600, xfx, $).


% ukapena adierazteko eragilea (bakarrik balio atomikoa duten ezaugarriekin)

:- op(500, xfx, ez).

% balio desberdinen aukeraketa adierazteko eragilea 
% (bakarrik balio atomikoa duten ezaugarriekin)
% lehen eragigaia ezaugarri baten izena edo balioa, eta bigarrena
% balio atomikoen multzoa

:- op(500, xfx, badago).

:- op(500, fx, edo).
:- op(500, fx, eta).
:- op(500, xf, definitua).

:- multifile (rule/2), (relax_spec/4), (dict/3).

% :- ensure_loaded(library(basics)). % quintus
:- use_module(library(lists)).       % sicstus
:- use_module(library(system)).       % sicstus


:- dynamic (dict/6), (dict/3), (lexema/4), (arku_zenbakia/1), (arku/5).        % sicstus




%-------------------------------------------------------------
% Parserra oso motela denez, erregelak eskubiko lehen
% elementuaren bidez indexatuko ditut
% Hau egiteko, erregelak banan-banan tratatuko dira, eta elementu horren 
% kategoria gehituko zaie hasieran
%-------------------------------------------------------------
erregelak_hasieratu :-
	(rule(I, (Ezkerra ---> Semeak@Murrizt))),
	lehen_aldagaia(Semeak, Ezkerra, Lehena),
	kategoria(Lehena, Murrizt, Kat_Zerrenda),
	foreach(member(Kat, Kat_Zerrenda), 
		assert(rule(Kat, I, (Ezkerra ---> Semeak@Murrizt)))),
	fail.

erregelak_hasieratu:-   % bukaeran erregela lexikoa tratatu
	(rule_lex(erregela_lexikoa, (Ezkerra ---> Semeak@Murrizt))),
	lehen_aldagaia(Semeak, Ezkerra, Lehena),
	kategoria(Lehena, Murrizt, Kat_Zerrenda),
	foreach(member(Kat, Kat_Zerrenda), 
		assert(rule_lex(Kat, erregela_lexikoa, (Ezkerra ---> Semeak@Murrizt)))),
	fail.
		
erregelak_hasieratu:-   % bukaeran post-erregela tratatu
	(rule_post(erregela_post, (Ezkerra ---> Semeak@Murrizt))),
	lehen_aldagaia(Semeak, Ezkerra, Lehena),
	kategoria(Lehena, Murrizt, Kat_Zerrenda),
	foreach(member(Kat, Kat_Zerrenda), 
		assert(rule_post(Kat, erregela_post, (Ezkerra ---> Semeak@Murrizt)))).





lehen_aldagaia([X], Ezk, X):-
	Ezk \==X.

lehen_aldagaia([X, Y], Ezk, X):-
	Ezk \==X,
	X \== Y.

lehen_aldagaia([X, Y, Z], Ezk, X):-
	Ezk \== X,
	X \== Y,
	X \== Z.
% baldintza horiek gero erregeletan ezkerraldeko edo ezkerreko lehena
% ez den beste elementu batekin ez bateratzeko jarri ditut




kategoria(_Elem, [], [_Ald_Berria]).
% ez bada kategoria aurkitu, orduan aldagai bat utziko da
% honek indexazioa moteltzea ekarriko du kasu horietan

kategoria(Elem, [X|_Y], Zerr) :-
	badago_kat(Elem, X, Zerr), !.




% bestela bilatu beste zatian
kategoria(Elem, [_X|Y], Z):-
	!, kategoria(Elem, Y, Z).



badago_kat(Ald, m(_, Ald2/oina/ezaug/nag/kat <=> Kat), [Kat]):-
	atomic(Kat), !,
	Ald == Ald2.


badago_kat(Ald, m(_, Ald2/oina/ezaug/nag/kat badago Zerrenda), Zerrenda):-
	Ald == Ald2.

% azken aukera hau kategoria hori definitu gabe egotea eskatzen denerako
badago_kat(_Ald, m(_, _Ald2/oina/ezaug/nag/kat badago []), []).






%----------------------------------------------------------------------------
%
%	PATR in Prolog:	interface.p
%	
%	Author:		Robert Dale (R.Dale@uk.ac.edinburgh)
%	Revisions:	Shona Douglas (S.Douglas@uk.ac.edinburgh) 
%	Date:		Tuesday 3rd September 1991
%	Notes:		This used to be part of the series of files
%			patr0912.p---patr0921.p

%----------------------------------------------------------------------------
%
%	The PATR Interface
%
% 	The following two predicates provide an interface 
%	between PATR entities---grammar rules and lexical 
%	entries---and the parser.
%
%----------------------------------------------------------------------------

%
%			Rules
%

%
%	rule(LHS, RHS, Relax_level)
%

% This predicate provides the interface between the parser and the 
% grammar rules. It finds a matching (binary) rule and solves all the 
% associated constraints that are applicable at the current relax_level.
%
% Essentially the predicate says:
% a category LHS is formed by categories X... in the list RHS at Relax_level iff
% -	there is a rule in the database with index I, of the form
%   	LHS ---> X... with some associated constraints; and
% -	the constraints  applicable at Relax_level  are satisfied.


erregela_aplikatu(Kat, I, LHS, RHS):-
	(rule(Kat, I, (LHS ---> RHS@Constraints))),
	% relax_level(Relax_record, R),
	% (relax_spec(I, Necessary_indices, Relax_templates, R) -> (true);
        %              (murrizpenen_lista(Constraints, Necessary_indices), Relax_templates = [])),
                          % ez badago erlajaziorik, orduan 4 murrizpen baldin badaude [1,2,3,4]
                          %   emango da,eta erlajazioen lista hutsa da 
	apply_constraints(Constraints),
	gune_ezaugarriak_goratu(LHS, RHS).

rule_lex(Kat, I, LHS, RHS):-
	(rule_lex(Kat, I, (LHS ---> RHS@Constraints))),
	% relax_level(Relax_record, R),
	% (relax_spec(I, Necessary_indices, Relax_templates, R) -> 
        %            (true);
        %            (murrizpenen_lista(Constraints, Necessary_indices), Relax_templates = [])),
                          % ez badago erlajaziorik, orduan 4 murrizpen baldin badaude [1,2,3,4]
                          %   emango da,eta erlajazioen lista hutsa da 
                           
               % (relax_spec(I, Necessary_indices, Relax_templates, 0))),
               % ez badago zehaztapenik maila horretan, 0. mailakoak aztertu
	apply_constraints(Constraints).
	% may_apply_constraints(Constraints,Relax_templates,Relax_record,New_relax_record).


rule_post(Kat, I, LHS, RHS):-
	(rule_post(Kat, I, (LHS ---> RHS@Constraints))),
	apply_constraints(Constraints).



gune_ezaugarriak_goratu(Ama, [Ezkerra, Eskubia]):-
	!,
	gune(Bidea, Ezaugarriak),
	goratu_ezaugarriak(Bidea, Ezaugarriak, Ama, Ezkerra, Eskubia).

	
gune_ezaugarriak_goratu(_LHS, [_Ezkerra]):- !. % seme bakarra badago, orduan ez da ezer gertatuko


goratu_ezaugarriak(_Bidea, [], _Ama, _Ezkerra, _Eskubia):- !.

goratu_ezaugarriak(Bidea, [Ezaug | Besteak], Ama, Ezkerra, Eskubia):-
	ebaluatu_bidea(Ama, Bidea, AmaBal), eval(AmaBal/Ezaug, AmaEzaugBal),
	(nonvar(AmaEzaugBal) ->
	    true;
	    ebaluatu_bidea(Eskubia, Bidea, EskBal), eval(EskBal/Ezaug,  EskEzaugBal),
	    (nonvar(EskEzaugBal) ->
		(EskEzaugBal = AmaEzaugBal);
		(ebaluatu_bidea(Ezkerra, Bidea, EzkBal), eval(EzkBal/Ezaug, EzkEzaugBal),
		(EzkEzaugBal = AmaEzaugBal)))),
        !, goratu_ezaugarriak(Bidea, Besteak, Ama, Ezkerra, Eskubia).



ebaluatu_bidea(Kat, E1/Besteak, Bal):-!,
	eval(Kat/E1, Bal1),
	ebaluatu_bidea(Bal1, Besteak, Bal).
ebaluatu_bidea(Kat, E1, Bal):-!, eval(Kat/E1, Bal).


relax_spec(xxxxxxxxxxxx,      [1,2,3,4,5,6,7,8,9],     [],       0).
% honek bakarrik balio du erabiltzen ez denean errorerik ez emateko (predikatu ez definitua)




murrizpenen_lista(C, L):- murrizpenen_lista(C, L, 1).

murrizpenen_lista([], [], _N) :- !.
murrizpenen_lista([_X|Y], [N | R], N) :- !, 
                    N1 is N + 1,
                    murrizpenen_lista(Y, R, N1).



/* 94-4-8 hemen "cut" kendu dut, bestela errore guztiak lehen erregelaren
erlajazioak zirelako beti. Honela beste erregelak ere probatzen dira */


%
%			Lexical Entries
%

%
%	lex(Hitz_zenbakia, Kat, Egitura, posizioa ).
%

banatuta:- banatuta_jarri(bai).
bilduta:- banatuta_jarri(ez).


banatuta_jarri(bai):-
	(retract(banatuta(_B)) -> true; true),
	assert(banatuta(bai)).
banatuta_jarri(ez):-
	(retract(banatuta(_B)) -> true; true),
% 	retract(banatuta(_B)),
	assert(banatuta(ez)).



hiztegia_hasieratu_morf:-
	banatuta(bai),
	!,
	hiztegia_hasieratu_morf_osagaien_zenbakiak_banatuta.
hiztegia_hasieratu_morf:-
	banatuta(ez),
	!,
	hiztegia_hasieratu_morf_osagaien_zenbakiak_bilduta.



% momentukoa: Kepak eta nik morfosintaxia eguneratzeko kenduta

hiztegia_hasieratu_morf_osagaien_zenbakiak_bilduta :-
	dict(Has, Buk, Egitura@Murrizt),
	  % dict(HZ, AZ, AA, MZ, AM, Egitura@Murrizt),
	solve(Murrizt),
	in(kat:Kat, Egitura),
%        banatu_ezaugarriak(Egitura, Egitura_irt), erregela lexikoa 
%         aplikatu hiztegiko elementuei
	rule_lex(Kat, erregela_lexikoa, Egitura_irt, [Egitura]),
	assert(lexema(Has, Buk, Kat, Egitura_irt)),
 	  % assert_lexema(HZ, AZ, AA, MZ, AM, Kat, Egitura_irt),
	fail.	

hiztegia_hasieratu_morf_osagaien_zenbakiak_bilduta.



% momentukoa: 2000-abendua, eguneraketa egiteko (datu_berri)
hiztegia_hasieratu_morf_osagaien_zenbakiak_banatuta :-
	%  dict(Has, Buk, Egitura@Murrizt),
	dict(HZ, AZ, AA, MZ, AM, Egitura@Murrizt),
	solve(Murrizt),
	in(kat:Kat, Egitura),
        kalkulatu(Has, Buk, HZ, AZ, AA, MZ, AM),
	rule_lex(Kat, erregela_lexikoa, Egitura_irt, [Egitura]),
	assert(lexema(Has, Buk, Kat, Egitura_irt)),
	fail.	

hiztegia_hasieratu_morf_osagaien_zenbakiak_banatuta.




% lehen eta azken morfema da
kalkulatu(Has, Buk, HZ, _AZ, _AA, 1, 0):- !,
	Buk is (HZ + 1) * 1000000,
	Has is HZ * 1000000.
% lehen morfema baina ez azkena
kalkulatu(Has, Buk, HZ, AZ, _AA, 1, 1):- !,
	Buk is (HZ * 1000000) + (AZ * 1000) + 1,
	Has is HZ * 1000000.
% azken morfema baina ez lehena
kalkulatu(Has, Buk, HZ, AZ, _AA, MZ, 0):- !,
	Buk is (HZ + 1)* 1000000,
	Has is (HZ * 1000000) + (AZ * 1000) + MZ - 1.
% erdiko morfema
kalkulatu(Has, Buk, HZ, AZ, _AA, MZ, _AM):- !,
	Buk is (HZ * 1000000) + (AZ * 1000) + MZ,
	Has is (HZ * 1000000) + (AZ * 1000) + MZ - 1.





% 	lexema(H, A, AA, MZ, AM, Kat, Egitura)
% honek hitz baten informazioa gordeko du



hiztegia_hasieratu_sint :-
	dict(Has, Buk, Egitura@Murrizt),
	solve(Murrizt),
	in(kat:Kat, Egitura),
	assert(lexema(Has, Buk, Kat, Egitura)),
	fail.	
hiztegia_hasieratu_sint.

	
% 	lexema(Hasiera, Bukaera, Kat, Egitura)
% honek hitz baten informazioa gordeko du


/* 
% lehen morfema bada, orduan hasiera X,0,0 modukoa izango da
% azken morfema bada, orduan hurrengo hitzera joango da
	      % adib: 1,1,1 -> 1,0,0    2,0,0
assert_lexema(HZ, _AZ, _AA, 1, 0, Kat, Egitura_irt):-
	!,
	Has is HZ*1000000,
	Buk is (HZ + 1)* 1000000,
	assert(lexema(Has, Buk, Kat, Egitura_irt)).

% lehen morfema ez bada,
% azken morfema bada, orduan hurrengo hitzera joango da
	      % adib: 1,1,2 -> 1,1,1 -> 2,0,0
assert_lexema(HZ, AZ, _AA, MZ, 0, Kat, Egitura_irt):-
	MZ > 1,
	!,
	Has is HZ*1000000 + AZ* 1000 + MZ - 1,
	Buk is (HZ + 1)* 1000000,
	assert(lexema(Has, Buk, Kat, Egitura_irt)).
	
% bestela, hurrengo morfemara joango da, hitz berean
% lehen morfema bada, hasiera X,0,0 modukoa da
	      % adib: 1,1,1 -> 1,0,0  1,1,1
assert_lexema(HZ, AZ, _AA, 1, 1, Kat, Egitura_irt):-
	!,
	Has is HZ * 1000000,
	Buk is HZ * 1000000 + AZ *1000 + 1,
	assert(lexema(Has, Buk, Kat, Egitura_irt)).
	
% bestela, hurrengo morfemara joango da, hitz berean
% lehen morfema ez bada, 
	      % adib: 1,1,2 -> 1,1,1  1,1,2
assert_lexema(HZ, AZ, _AA, MZ, 1, Kat, Egitura_irt):-
	MZ >1,
	!,
	Has is HZ * 1000000 + AZ * 1000 + MZ - 1,
	Buk is HZ * 1000000 + AZ * 1000 + MZ,
	assert(lexema(Has, Buk, Kat, Egitura_irt)).
*/


%----------------------------------------------------------------------------
%
%	PATR in Prolog:	pretty_printer.p
%	
%	Author:		Robert Dale (R.Dale@uk.ac.edinburgh)
%	Revisions:	Shona Douglas (S.Douglas@uk.ac.edinburgh) 
%	Date:		Tuesday 3rd September 1991
%	Notes:		This used to be part of the series of files
%			patr0912.p---patr0921.p

%----------------------------------------------------------------------------
%
%	Pretty Printer
%
%	Liberally stolen from Peter Yule; modified to indent each line 
%	to a varying extent depending on the length of the labels
% 	printed so far.  Needs some cleaning up.
%       Needs some work before it does anything really useful: it
%	should work out indents on the basis of the lengths of labels.
%

ppc(X) :- ppc(1,0,X).

ppc(0,Tab,A) :-
        var(A),
        !,
        pp(0,Tab,'*'),		% aldagaien zenbakien ordez asteriskoa idatziko da
        nl.
ppc(_X,_Tab,A) :- var(A),!.               /* for terminal var, do nothing */

ppc(_X,_Tab,[]) :- !.               /* lista hutsa, ez idatzi ezer*/


ppc(X,Tab,analisia(A)) :- !, 
			ppc(X,Tab,'analisia'),         
                        Tab1 is Tab + 8,   
        		ppc(1,Tab1,A).        
				% bestela listako balioak idatzi

ppc(X,Tab,[osagaia(A)|Rest]) :- !, 
			ppc(X,Tab,'osagaia'),         
                        Tab1 is Tab + 5,   
        		ppc(1,Tab1,A), % lehen elementua idatzi        
        		ppc(1,Tab,Rest).        
				% bestela listako balioak idatzi


ppc(X,Tab,[morf(A)|Rest]) :- !, 
			ppc(X, Tab, 'morf'),         
                        Tab1 is Tab + 5,   
        		ppc(1, Tab1, A), % lehen morfema idatzi        
        		ppc(1, Tab, Rest).        
				% bestela listako balioak idatzi

ppc(X, Tab,['Gako'(A)|Rest]) :- !, 
			% ppc(X, Tab, 'Gako'),         
                        % Tab1 is Tab + 5,   
        		ppc(X, Tab, A), % lehen gakoa idatzi        
        		ppc(X, Tab, Rest).        
				% bestela listako balioak idatzi

ppc(_X, _Tab, [fs(A)|Rest]) :- !, 
                        % nl, tabs(Tab),
        		idatzi_funtzioak([fs(A)|Rest]).        
				




ppc(X,Tab,[Feat|Rest]) :- !,            /* print member of list */
	(number(Feat) -> (write(' '), ascii_lista_idatzi([Feat | Rest]), nl);
				% lehena zenbakia bada, orduan ASCII kodeak dira

			(ppc(X,Tab,Feat),         /* on same line if first */
        		ppc(1,Tab,Rest))).         /* print rest on lower lines */
				% bestela listako balioak idatzi


ppc(X,Tab,F:V) :- !,                    % ezaugarri hauek ez dira idatziko:
					% hzenb anzenb azkenanal morfzenb azkenmorf
	( (idaztekoa(F),
           \+var(V),
           \+denak_aldagaiak(V),
           \+V = [])    ->  % ez idatzi balioa(k) aldagaia(k) edo lista hutsa badira

					/* to print feature-value pair */
         (pp(X,Tab,F),                    /* print the feature */
	  name(F,String),		% Mod by RDA:  changed indentation
	  length(String,Length),	% to take account of length of labels
	  RealLength is Length + 1,	% Add one for space in between.
          Tab1 is Tab + RealLength,      % Calculate new indent value.
          ppc(0,Tab1,V)); 		/* print V beginning on same line */
	 true).           

ppc(X,Tab,A) :-                         /* print atom value + newline */
        pp(X,Tab,A),
        nl.

pp(X,Tab,A) :-                          /* X is 1 or 0 */
        Ntab is (X*Tab)+(1-X),          /* if X=1, Ntab=Tab; if X=0, Ntab=1 */
        tabs(Ntab),                     /* print Ntab tabs */
        aztertu_eta_idatzi(A).                       /* then print the atom */

tabs(0) :- !.                           /* tabs/1 prints X tab characters */
tabs(X) :-
        write(' '),
        X1 is X - 1,
        tabs(X1).


idatzi_funtzioak([]) :- !,  nl. % lerro berean idazteko
idatzi_funtzioak([fs(A)|Rest]) :- write(' '), ascii_lista_idatzi(A), 
                                  idatzi_funtzioak(Rest).



idatzi_id_ak([]) :- !,  nl.
idatzi_id_ak([ID_l | Beste_ID_ak]) :-
	!,
	idatzi_id_ak2(ID_l), nl,
	idatzi_id_ak(Beste_ID_ak).	
idatzi_id_ak2([]) :- !,  nl. 
idatzi_id_ak2([ID | Besteak]) :- write(' '), name(ID2, ID), write(ID2),
	idatzi_id_ak2(Besteak).



% bi aukera daude idazteko:
% 'izena' edo [112, 103, 104, 105]
ascii_lista_idatzi([]):- !.
ascii_lista_idatzi([A| B]):- number(A), !, put(A), ascii_lista_idatzi(B).
ascii_lista_idatzi(N):- !, write(N).

ascii_lista_idatzi(_Fitx, []):- !.
ascii_lista_idatzi(Fitx, [A| B]):- number(A), !, put(Fitx, A), ascii_lista_idatzi(Fitx, B).
ascii_lista_idatzi(Fitx, N):- !, write(Fitx, N).







aztertu_eta_idatzi(X) :- (atom(X); number(X)), !, write(X).

aztertu_eta_idatzi(X) :- name(X1, X), write(X1).


idaztekoa(Ezaugarri_izena) :- 	((Ezaugarri_izena = hzenb);
				 (Ezaugarri_izena = anzenb);
				 (Ezaugarri_izena = azkenanal);
				 (Ezaugarri_izena = morfzenb);
				 (Ezaugarri_izena = azkenmorf)), !, fail.

idaztekoa(_Ezaugarri_izena). % lista horretako balioa ez bada, idatzi behar da


denak_aldagaiak(V):- var(V), !. % egiazkoa ezaugarri-zerrendako balio guztiak aldagaiak badira
denak_aldagaiak([]):- !. % egiazkoa ezaugarri-zerrendako balioa zerrenda hutsa bada,
                         %   adib.; fsl:[]



denak_aldagaiak([_F:V|Rest]):- denak_aldagaiak(V), denak_aldagaiak(Rest).



%
%----------------------------------------------------------------------------



%----------------------------------------------------------------------------
%
%	PATR in Prolog:	interpreter.p
%	
%	Author:		Robert Dale (R.Dale@uk.ac.edinburgh)
%	Revisions:	Shona Douglas (S.Douglas@uk.ac.edinburgh) 
%	Date:		Tuesday 3rd September 1991
%	Notes:		This used to be part of the series of files
%			patr0912.p---patr0921.p

%----------------------------------------------------------------------------
%
%	The PATR Interpreter
%	
%	In order to determine if a grammar rule or a lexical entry 
%	can be used at some point in a parse, we have to see if the
%	specified constraints hold.  These predicates carry out this
%	operation.
%
%	Exactly what these predicates do depends on where they are
%	called and on the parsing regime used.  Here, where we are using
%	a bottom-up parser, calls in aid of lexical entries build up new
%	feature structures from the list of constraints provided; these
%	calls will always succeed once the lexical entry corresponding
%	to a given word has been retrieved.  Calls in aid of rules, on
%	the other hand, may augment structure also, but their
%	fundamental job will be to see if two structures to be combined
%	are in fact compatible.  These calls may, therefore, fail.
%
%----------------------------------------------------------------------------

%
%	solve(Constraint_list)
%

% Takes a list of constraints, each of which is of the form X <=> Y, 
% and calls each in turn.  
%
% In the case of bottom-up parsing, for lexical entries this means
% building a feature structure that corresponds to the list of
% constraints; in the case of rules, this means checking to see whether
% the constraints hold, and perhaps adding new information to the
% existing structures.

% Adding relax_level information to constraint records  means that solve/1 
% must have a way of stripping off this control information to get back to 
% the bare constraint:

solve([]):-!.
solve([m(_, Eq)|C_rs]):-
	call(Eq),
	solve(C_rs).


solve_bat(Eq):- call(Eq).

%
%	X <=> Y
%

% This is the graph equality predicate.  It evaluates both its arguments
% to feature structures, and then attempts to unify them.
%
% In effect, the two arguments, which are paths, are specifications of
% graphs.  We build the graphs denoted by these specifications and then
% attempt to unify them.

X <=> Y:-
        eval(X, EvaluatedX),
        eval(Y, EvaluatedY),
        unify(EvaluatedX, EvaluatedY).


% ukapena baldin badago, orduan konprobatu egingo da lehen argumentua
% bigarren argumentuan agertzen den listakoa den

Elem ez Lista :-
	eval(Elem, Elem_ebal),
	eztago(Elem_ebal, Lista).
	

eztago(Elem, _X) :- var(Elem), !.
% aldagaia bada, orduan egiazkoa
% hau oso diskutigarria izan daiteke !!!!


eztago(Elem, [Elem|_Y]) :- !, fail.
% Koldo 2003-VII-24
%eztago(Elem, [Elem2 | _Y]) :-
%	name(Elem2, Elem),
%	!,
%	fail.

eztago(Elem,[_X|L]) :- eztago(Elem, L).

eztago(_Elem, []).



% predikatu honek egiazkoa emango du elementua listan badago
% Elementu aldagaia bada, orduan balio faltsua bueltatzen du

Elem badago Lista :- 
	eval(Elem, Elem_ebal),
	dago(Elem_ebal, Lista).

dago(Elem, _L):- var(Elem), !, fail.


dago(_Elem, []):- !, fail.

dago(Elem, [Elem |_Y]):- !.
% ez dut "cut" jartzen, horrela lehen elementua aldagaia izanez gero
% elementu bakoitzeko instantziatuko da

% Koldo. komentatuta 2003-VII-24. 
%dago(Elem, [Elem2 | _Y]):- 
% batzuetan bilatu nahi den elementua komatxo artean doa, baina listetan denak jarri
% ditut komatxorik gabe, eta orduan honako kasuak gertatuko dira:
% hau   badago [hau, hori, hura]
% "hau" badago [hau, hori, hura]
%	name(Elem2, Elem),
%	!.

	
dago(Elem, [_X|Y]) :-
	dago(Elem, Y).



% predikatu hau bete egingo da elementua aldagaia ez bada, hau da, eskatuko da
% balio bat izatea, adib.: X/morf definitua (lema bat bada ez da beteko)
Elem definitua :- 
	eval(Elem, Elem_ebal),
	nonvar(Elem_ebal).




% predikatu honek aukera adieraztea onartuko du: egiazkoa izango da
%  murriztapen bat egiazkoa bada.
%	formatua: edo([murrizt1, murrizt2, ...])

edo([Eq1 | _Besteak]):- call(Eq1), !.

edo([_Eq1 | Besteak]):- edo(Besteak).

edo([]) :- fail, !.


% predikatu honek "eta" adieraztea onartuko du: egiazkoa izango da
%  murriztapen guztiak egiazkoak badira.
%	formatua: eta([murrizt1, murrizt2, ...])

eta([Eq1 | Besteak]):- call(Eq1), eta(Besteak).

eta([]) :-  !.






%
% 	eval(Graph_spec, Graph)
%

% This is the predicate which provides the crucial step in interfacing
% the PATR formalism and the graph unification mechanism.  We can't just
% directly see if two structures unify by saying
%
%	X1/agr <=> X2/agr
%
% We need to convert each side of the equation to a feature structure,
% and then see if the two structures are unifiable.  The eval predicate
% carries out this conversion.
%
% So, the first argument is a specification of a graph in terms of a
% constraint; the second argument is the graph denoted by this
% specification. 
%
% The rules for evaluation are as follows:
%
% -   the denotation of a variable is a variable
% -   the denotation of a path specification described as 
%     (graph-specification/feature) is the value of the evaluation of 
%     the feature in the graph denoted by the graph-specification.
% -   the denotation of a constant is a constant.
%

% If the first argument is a variable, then it can already stand for 
% a [Name:Value|_] construction, so we don't need to change anything.

eval(X, X):- 
        var(X), !.

% Koldo:
% predikatu honek kateen kateaketa lortzen du

eval($(A, B), Rl) :- !,
	eval(A, Aev), nonvar(Aev),
	eval(B, Bev), nonvar(Bev),
	izena(Aev, Al),
	izena(Bev, Bl),
 	append(Al, Bl, Rl).
%	name(R, Rl).


% gehitu_aurrizkia funtzioak bi kate hartuta konposatu egiten ditu:
% Adibidez: gehitu_aurrizkia("@JADNAG_MP_", Fs)
% Fs = ["@SUBJ", "@OBJ"]
% Hau emango du: ["@JADNAG_MP_SUBJ", "@JADNAG_MP_OBJ"]
% Hau da, bigarren listako elementuei funtzio sintaktikoaren marka (@) kenduko zaio
eval(gehitu_aurrizkia(Aurr, FSL), Em) :- 
	eval(Aurr, AEv), nonvar(AEv),
	eval(FSL, FSLEv), nonvar(FSLEv),
	gehitu_aurrizkia(AEv, FSLEv, Em).
gehitu_aurrizkia(_A, [], []) :- !.
gehitu_aurrizkia(AEv, [FS | Besteak], [FS_lista | R1]) :- !,
	izena(AEv, Al),
	izena(FS, [_Arroba | Funtzioa]),
 	append(Al, Funtzioa, FS_lista),
	% name(FS_berria, FS_lista),
	gehitu_aurrizkia(AEv, Besteak, R1).




%nire predikatua definitu dut, zuzenean "name" deitzen bada
% errorea ematen duelako hitz konposatuekin

izena(S, I):-	
	(atom(S); number(S)), name(S, I), !.

izena(S, S).


% predikatu honek fsl1, fsl2, ... elementuen lista osatuko du
eval(sortu_fsl(Elem), R):- sortu_fsl(Elem, 1, R), !.

sortu_fsl(Elem, Zenb, [Balioa| R1]) :- 
                            osatu_zenbakia("fsl", Zenb, FSl), 
                            name(FSatom, FSl),
                            eval(Elem/FSatom, Balioa), 
                            \+var(Balioa), !, % baliorik badu, ez bilatu gehiago
                            Zenbberria is Zenb + 1,
                            sortu_fsl(Elem, Zenbberria, R1).

sortu_fsl(_Elem, _Zenb, []). 


osatu_zenbakia(L, Zenb, R) :- name(Zenb, ZL), append(L, ZL, R).


% 2005-V- 23 predikatu honek Etik1, Etik2, ... elementuen lista osatuko du, adib. hobetsiak1, hobetsiak2, ...
% Lista bakoitzak bikoteak ditu: [sarrera, homografoid]
% Etik_Irt da bukaerako listan elementu bakoitzak izango duen etiketa, adib.: ['Gako'(...), 'Gako'(...)]
eval(sortu_hobetsiak_estandarrak_lista(Etik_Sar, Elem, Etik_Irt), R):- sortu_hobetsiak_estandarrak_lista(Etik_Sar, Elem, Etik_Irt, 1, R), !.

sortu_hobetsiak_estandarrak_lista(Etik_Sar, Elem, Etik_Irt, Zenb, [Term| R1]) :-
	                          name(Etik_Sar, Etik_l),
                                  osatu_zenbakia(Etik_l, Zenb, Etik_l_zenb), 
                                  name(FSatom, Etik_l_zenb),
                                  eval(Elem/FSatom, Balioa),
                                 \+var(Balioa), !, % baliorik badu, ez bilatu gehiago
				  itzuli_sarrera_Sarrera(Balioa, Balioa_itzulita),
				  Term =.. [Etik_Irt, Balioa_itzulita],  % adib.: Term = .. ['Gako', Info] sortuko du Gako(Info) terminoa
                                  Zenbberria is Zenb + 1,
                                  sortu_hobetsiak_estandarrak_lista(Etik_Sar, Elem, Etik_Irt, Zenbberria, R1).

sortu_hobetsiak_estandarrak_lista(_Etik_Sar, _Elem, _Etik_Irt, _Zenb, []). 


% ['sarrera':a, 'homografo-id':b] hau bihurtzen du:  ['Sarrera':a, 'homografo-id':b]
itzuli_sarrera_Sarrera(Balioa, Balioa_itzulita):-
	eval(Balioa/sarrera, Sar),
	eval(Balioa_itzulita/'Sarrera', Sar),
	eval(Balioa/'homografo-id', HID),
	eval(Balioa_itzulita/'homografo-id', HID).



% Koldo:
% predikatu honek ezaugarri-egituren lista lortzen du
% gehitu(A, B, C)    A hutsa edo lista bat da, osagaia(C) elementuko lista
%                    emaitza lista bat da, A hutsa baldin bada, osagaia(B) + osagaia(C) bukaeran duena
%                                                  bestela A + osagaia(C)

eval(gehitu_osagai_listak(Osagaiak, Dena, B), R) :- !,
	eval(Osagaiak, Osagaiakev),
	eval(Dena, Denaev),
	eval(B, Bev),
 	gehitu_osagai_listak(Osagaiakev, Denaev, Bev, R).

gehitu_osagai_listak(A, B, C, [osagaia(B), osagaia(C)]):- var(A), !. % aldagaia bada, hutsa dago
gehitu_osagai_listak(Lista, _B, C, Em):- gehitu_elem(Lista, C, Em).

gehitu_elem([], B, [osagaia(B)]).
gehitu_elem([osagaia(X)|Y], B, [osagaia(X)|Em]):- gehitu_elem(Y, B, Em).



eval(bateko_morf_lista_osatu(Morfema), [morf(Morfema)]) :- !.


% gehitu(O1, D1, O2, D2)    O1, O2 hutsak edo listak dira, osagaia(C) elementuen lista
%                    emaitza lista bat da, O1 eta O2 hutsak baldin badira, osagaia(D1) + osagaia(D2) bukaeran 
%                                          O1 hutsa bada, orduan osagaia(D1) + O2
%                                          O2 hutsa bada, orduan O1 + osagaia(D2)
%                                          O1 eta O2 ez badira biak hutsak, orduan O1 + O2

eval(gehitu_morf_lista(Lista1, Lista2), R) :- !,
	eval(Lista1, Lista1ev),
	eval(Lista2, Lista2ev),
 	gehitu_morf_lista(Lista1ev, Lista2ev, R).

gehitu_morf_lista(L1, L2, _) :- var(L1), var(L2), !. 
            % morfemen listak hutsak dagoz, 
            % emaitza hutsa da (adibidez: ber + erabili (biak dira lemak))

gehitu_morf_lista(L1, L2, L2) :- var(L1), !. 
gehitu_morf_lista(L1, L2, L1) :- var(L2), !. 
gehitu_morf_lista(L1, L2, L3) :- gehitu_elem_morf_listak(L1, L2, L3), !. 

gehitu_elem_morf_listak([], L2, L2).
gehitu_elem_morf_listak([X|Y], L2, [X|Em]) :- gehitu_elem_morf_listak(Y, L2, Em).


% Aldaerak konbinatzeko aukerak, 2 osagaien artean (lema+lema edo lema+morfema), 4 kasu ikusten ditut:
%  * 2 osagaiak ez dira aldaerak: emaitza kate hutsa
%  * 1 aldaera eta bestea ez. Orduan konbinatu aldaera dena bestearen lema_osatua-rekin
%  * 2 osagaiak dira aldaerak. Orduan lotu biak.
eval(osatu_aldaeraren_informazioa(X1, X2), "") :-
             eval(X1/aldaera_osatua, ""),
             eval(X2/aldaera_osatua, ""),
             !.
eval(osatu_aldaeraren_informazioa(X1, X2), AO) :-
             eval(X1/aldaera_osatua, ""), % orduan 2garrena aldaera da eta lehenengoa ez!
             eval(X1/lema_osatua,    LO1),
             eval(X2/aldaera_osatua, AO2),
             eval($(LO1, $("+", AO2)), AO),
             !.
eval(osatu_aldaeraren_informazioa(X1, X2), AO) :-
             eval(X2/aldaera_osatua, ""), % orduan 1garrena aldaera da eta bigarrena ez!
             eval(X2/lema_osatua,    LO2),
             eval(X1/aldaera_osatua, AO1),
             eval($(AO1, $("+", LO2)), AO),
             !.
eval(osatu_aldaeraren_informazioa(X1, X2), AO) :- % biak dira aldaerak!
             eval(X1/aldaera_osatua,    AO1),
             eval(X2/aldaera_osatua,    AO2),
             eval($(AO1, $("+", AO2)), AO),
             !.




% Ondorengoak aurrizki eta atzizki listak tratatzeko dira. Lista hauek modu honetakoak dira: [Etiketa(tze), Etiketa(txo)]
eval(gehitu_listan_hasieran(AurL, Etiketa, Sarrera), R) :- !,
	eval(AurL,    AurLev),
	eval(Sarrera, Sarreraev),
 	gehitu_listan_hasieran(Sarreraev, Etiketa, AurLev, R).

% 2005-V-31
gehitu_listan_hasieran(Sarrera,  Etiketa, AurL, [Term]) :-  var(AurL), !, Term =.. [Etiketa, Sarrera]. 
            % aurrizkien lista hutsa dago, 
            % emaitza aurrizki bakarreko lista da

% 2005-V-31
gehitu_listan_hasieran(Sarrera, Etiketa, AurL, [Term | AurL]) :- Term =.. [Etiketa, Sarrera], !.



eval(gehitu_listan_bukaeran(Lista1, Etiketa, Atz), R) :- !,
	eval(Lista1, Lista1ev),
	eval(Atz,    Atzev),
 	gehitu_listan_bukaeran(Lista1ev, Etiketa, Atzev, R).

gehitu_listan_bukaeran(L1, Etiketa, Atz, [Term]) :- Term =.. [Etiketa, Atz], var(L1), !. 
            % atzizkien lista hutsa dago, 
            % emaitza atzizki bakarreko lista da

gehitu_listan_bukaeran(L1, Etiketa, Atz, L3) :- Term =.. [Etiketa, Atz], append(L1, [Term], L3).







nagusia(X) :- eval(X/nag/kat, Kat), member(Kat, [ize, ior, adi, adl, adt, adj, adb, pro, det, eli, izeeli]).



% Get the value V of something that evaluates to feature EN within
% the graph EF, which is recursively computed.

% If the first argument is of the form F/N, then we need to do some
% work. We submit both sides of the slash to eval; because of the
% associativity of /, N will be atomic, but F may be complex and thus
% will have to be recursed down.  
%
% We then see if EN:V (where V is so far unspecified) is present in EF.

eval(F/N, V):- !, 
        eval(N, EN),
        eval(F, EF), 
        in(EN:V, EF).

% Constants evaluate to themselves:

eval(X,X).

% in/2
%
% This predicate takes a Feature:Value pair and a feature structure
% (i.e., a list of Feature Value pairs).  The predicate succeeds if the
% feature structure contains the feature-value pair.
%
% In the present context, when called in aid of building the structure 
% corresponding to a word, it adds the Feature:Value pair to the feature
% structure.  When called in aid of a rule application, it may either
% check that a specified Feature:Value pair is present in the feature
% structure, or in the case of a Feature:Value pair where the Value is a
% variable, it may find a value for that variable (or at least unify it
% with another variable).

in(F:V,[F:V1|_]):- !,
        V = V1.

in(E, [_|T]):-
        !, in(E, T).

% SGML-ratzerako predikatua:
in(Ezaugarria, Bal, Egitura) :- in(Ezaugarria:Bal, Egitura).


%
%----------------------------------------------------------------------------


%----------------------------------------------------------------------------
%
% relax_spec(Rule_index, Necessary_indices, Relax_packages, Relax_level).
%
%----------------------------------------------------------------------------


rule_index(relax_spec(I, _, _, _, _), I).
necessary_indices(relax_spec(_, N, _, _), N).
relax_template(relax_spec(_, _, R, _), R).
relax_threshold(relax_spec(_, _, _, L), L).

% For each rule with index rule_index, at each relax_level there is a set
% of  the necessary_indices of  those constraints that must be applied at 
% that level, and a set of relax_templates, which specify the various 
% relaxations that can be performed at that level.
%
% The constraints are ordered in such a way as 
%	1. To minimise unnecessary structure building.  Thus, constraints that
%	are 'conditionals' in interpretation are placed first.
%	2. To perform structure-building in a desirable order, so as to produce 
%	a sensible looking output, that is, the cat is done first, attributes of
%	the structure next, then constituent structure, with daughters/first
%	before daughters/rest/first, and so on.  

%
% relax_template(Indices, Message).
%

relax_indices(relax_template(X,_Y),X).
error_message(relax_template(_X, Y),Y).


%
% relax_package(Constraints, Message).
%

error_message(relax_package(_X, Y),Y).
relaxed_constraints(relax_package(X,_Y),X).






%
%----------------------------------------------------------------------------

%----------------------------------------------------------------------------
%
%	Access functors for m
%
%----------------------------------------------------------------------------

% The relaxation method  in sheep_from_goats/4  means that constraints
%  must have some index attached to them...

index(m(Index, _), Index).
constraint(m(_, Constraint), Constraint).






%----------------------------------------------------------------------------
%
%	PATR in Prolog:	relaxation.p
%	
%	Author:		Robert Dale (R.Dale@uk.ac.edinburgh)
%	Revisions:	Shona Douglas (S.Douglas@uk.ac.edinburgh) 
%	Date:		Tuesday 3rd September 1991
%	Notes:		This used to be part of the series of files
%			patr0912.p---patr0921.p
%			
%			Monday 23 September
%		Changed the way optional constraints are selected, to allow sets
%		of constraints to be applied together or not at all.  Now all such
%		sets, for each rule, for each relax_level, are represented explicitly 
%		relax_record/4, which replaces relax_level/3.  
%			Added:
%				select_constraint/4
%				select_constraints/3 and /4
%				select_constraint_sets/3 and /4
%				relax_record/4

%----------------------------------------------------------------------------
%
%	Relaxation Mechanism
%
%----------------------------------------------------------------------------


%
% apply_constraints(Constraints, Indices).
%

apply_constraints([]):-!.
apply_constraints([C | Besteak]):-
	solve([C]),
	apply_constraints(Besteak).

% The above assumes that the given constraint for the index will always be 
% present; this should be the case if the tables are not incorrect.

%
% select_constraint(Constraints, Index, Constraint).
%

select_constraint([C|_Constraints], I, C):-
	index(C, I),!.
select_constraint([_C1|Constraints], I, C):-
	select_constraint(Constraints, I, C).

%
% may_apply_constraints(Constraints, Relax_templates, Relax_record, 
%			Relax_record).
%

% All possible Relax_packages have been tried, so no further changes to
% Relax_record:

may_apply_constraints(_Constraints, [], Relax_record, Relax_record).
	
% A relax_template is successfully applied: the changes to the Constraints, and
% thus to the constituents in the calling procedure rule stand, and the rest of
% the possible relaxations are tried:

may_apply_constraints(Constraints, [Relax_template|Rest], R, New_R):-
	relax_indices(Relax_template, I_set),
	apply_constraints(Constraints, I_set), !,
	may_apply_constraints(Constraints, Rest, R, New_R).

/* 94-4-8 "cut" jarri dut horrela, pakete batean multzo desberdinak daudenean eta bat
relajatzen denean beste multzo guztien konbinazio posible guztiak ez emateko */




% Otherwise, record the constraints that failed to be solved, before going on to
% try the rest of the possible relaxations:

may_apply_constraints(Constraints, [Relax_template|Rest], R, Final_R):-
	relax_packages(R, R_ps),
	relax_level(R, R_l),
	relax_level(New_R, R_l),
	instantiate_relax_template(Constraints,
		Relax_template,
		Relax_package),
	relax_packages(New_R, [Relax_package|R_ps]),
	ez_maximoa([Relax_package|R_ps]),
% errore-kopuru maximoa baino gehiago badira, ez aztertu
	may_apply_constraints(Constraints,
		Rest,
		New_R,
		Final_R).



errore_kopuru_maximoa(2).

ez_maximoa(L) :-
	elem_kop(L, E),
	errore_kopuru_maximoa(K),
	E =< K.

elem_kop([], 0).

elem_kop([_X|Y], K):-
	elem_kop(Y, K1),
	K is K1 + 1.



%
% instantiate_relax_template(Constraints, Relax_template, Relax_package).
%

instantiate_relax_template(Constraints,
		relax_template(Indices, S),
		relax_package(Relaxed_constraints, S)):-
	select_constraint_set(Constraints, Indices, Relaxed_constraints).


%
% select_constraint_set(Constraints, Indices, Cs)
%

select_constraint_set(Constraints, Indices, Cs):-
	select_constraint_set(Constraints, Indices, [], Cs).

select_constraint_set(_Constraints, [], Cs, Cs).
select_constraint_set(Constraints, [I|Indices], Old_Cs, Cs):-
	select_constraint(Constraints, I, C1),
	select_constraint_set(Constraints, Indices, [C1|Old_Cs], Cs).








%----------------------------------------------------------------------------
%
%	PATR in Prolog:	parser.p
%	
%	Author:		Robert Dale (R.Dale@uk.ac.edinburgh)
%	Revisions:	Shona Douglas (S.Douglas@uk.ac.edinburgh) 
%	Date:		Tuesday 3rd September 1991
%	Notes:		This used to be part of the series of files
%			patr0912.p---patr0921.p
%
%			Monday 23 September
%			Changed parse/5 to succeed on, and return, only successful parses.


%----------------------------------------------------------------------------
%
%	A Shift-Reduce Parser with relaxation
%
% 	Call this, for example, with something like
%
%	parse([], Result, 0, [the,dog],[]).



azken_nodoa(Z) :-
	azken_nodoa(1000000, Z).
azken_nodoa(H, H2) :-
	lexema(H, _Buk, _Kat, _Egitura), !,
	H1 is H + 1000000,
	azken_nodoa(H1, H2).
azken_nodoa(H, H).




hurrengo_hitza_nodoa(Has, Buk, Kat, Egitura1):-
	lexema(Has, Buk, Kat, Egitura),
	copy(Egitura, Egitura1).
% azken morfema ez bada, orduan nodoak hitzaren zenbakia hartuko du




%
%----------------------------------------------------------------------------


% Parser berria 95-4-29


% Ezaugarri-egiturak kopiatzeko predikatua

% Ez dut kontutan hartuko "reentrancy", hau da, egituretan
% balioak edo atomikoak edo aldagaiak dira

copy(A, _B) :- var(A), !.

copy(A, A) :- atomic(A), !.

copy(osagaia(A), osagaia(B)) :- copy(A, B), !.
copy(morf(A), morf(B)) :- copy(A, B), !.
copy('Gako'(A), 'Gako'(B)) :- copy(A, B), !.
copy(fs(A), fs(B)) :- copy(A, B), !.

copy(A:B, A:C) :- copy(B, C), !.

copy([A|B], [C|D]) :- copy(A, C), copy(B, D), !.


chart_hasieratu(Nodo_zenb) :-
	hurrengo_hitza_nodoa(Nodo_zenb, _N1, _Kat, _Egitura),
	!,
	foreach(hurrengo_hitza_nodoa(Nodo_zenb, N1, Kat, Egitura),
		tratatu_morf_sek(Nodo_zenb, N1, Kat, Egitura)),
	H1 is Nodo_zenb + 1000000,
	!,
	chart_hasieratu(H1).
% horrela, hitz bakoitzaren nodoak ordenatuta tratatzen dira

chart_hasieratu(_N).



foreach(X, Y) :-
	X,
	do(Y),
	fail.

foreach(_X, _Y):-
	true.
do(Y):- Y, !.



tratatu_morf_sek(Has, Buk, Kat, Egitura) :- 
	0 is Buk mod 1000000, % hau da, hitz berria hasten da, orduan ez jarraitu
	!, 
	arku_berria(Arku_zenb),
	erregela(Info, 0),
	semea(Info, 0),
	arku_zenb(Info, Arku_zenb),
	aztertu(Arku_zenb, Has, Buk, [Kat, Egitura], Info).



tratatu_morf_sek(Has, Buk, Kat, Egitura) :- 
	arku_berria(Arku_zenb),
	erregela(Info, 0),
	semea(Info, 0),
	arku_zenb(Info, Arku_zenb),
	aztertu(Arku_zenb, Has, Buk, [Kat, Egitura], Info),
	hurrengo_hitza_nodoa(Buk, N1, Kat1, Egitura1),
	tratatu_morf_sek(Buk, N1, Kat1, Egitura1).
	




% predikatu hau da parserraren oinarria:
% sortutako "edge" bat emanda, bera hartuta lortzen diren
% "edge"ak lortuko ditu, eta bakoitzarekin prozesu bera errepikatuko da.



aztertu(Arku_zenb, Has, Buk, [Kat, Egitura], Info) :- 
	assert(arku(Arku_zenb, Has, Buk, [Kat, Egitura], Info)),
	assert(atera_arku(Has, Buk, Arku_zenb)), % &&&&&&&&&
	assert(iritsi_arku(Buk, Has, Arku_zenb)),
	elem_bateko_erregelak(arku(Arku_zenb, Has, Buk, [Kat, Egitura], Info)),
	elem_biko_erregelak(arku(Arku_zenb, Has, Buk, [Kat, Egitura], Info)).  



% Hobekuntza: erlaxazio-maila batean bakarrik sortuko da elementu berria kasu bitan:
%             - erregelak erlaxazioak ditu maila horretan
%             - erregelak ez, baina osagaiak maila horretan sortu dira, 
%               erlaxazio baten bidez
% Hau da, 0garren mailako arkuak ez dira berriro sortuko beste mailetan
% Beste mailetakoak bai, zeren 1. mailan sortutako osagaia ez dakigu
% 2.enean sortu behar den ala ez (eta ezin da mantendu, bigarren mailan 
% berriro sortuko litzatekeelako (hau ebitatzeko osagai bakoitzak esan beharko luke
% erlaxatutako baldintzak, eta hau oso konplikatua da)


elem_bateko_erregelak(arku(_AZ, V1, V2, [Kat, Egitura], Info)) :-
	erregela_aplikatu(Kat, Rzenb, LHS, [Egitura]),
	copy(LHS, LHS1),
	arku_berria(Arku_zenb),
	solve_bat(LHS1/ezaug/kat <=> Balioa),
	% in(nag:Nag, LHS1),
	% in(kat:Balioa, Nag),
	erregela(Info_berri, Rzenb),
	arku_zenb(Info, N),
	semea(Info_berri, N),
	arku_zenb(Info_berri, Arku_zenb),
	aztertu(Arku_zenb, V1, V2, [Balioa, LHS1], Info_berri),
	fail.
	
elem_bateko_erregelak(_I).


elem_biko_erregelak(arku(_AZ, V1, V2, [_Kat2, Egitura2],Info2)) :-
	iritsi_arku(V1, V0, Arku_zenb1),
	arku(Arku_zenb1, V0, V1, [Kat1, Egitura1], Info1),
	% copy(Egitura1, Egitura1k),
	% copy(Egitura2, Egitura2k),
	erregela_aplikatu(Kat1, Rzenb, LHS, [Egitura1, Egitura2]),
	copy(LHS, LHS1),
	arku_berria(Arku_zenb),
	solve_bat(LHS1/ezaug/kat <=> KatLHS),
	% in(nag:Nag, LHS1),
	% in(kat:KatLHS, Nag),
	erregela(Info_berri, Rzenb),
	arku_zenb(Info1, N1),
	arku_zenb(Info2, N2),
	semeak(Info_berri, N1, N2),
	arku_zenb(Info_berri, Arku_zenb),
	aztertu(Arku_zenb, V0, V2, [KatLHS, LHS1],Info_berri),
	fail.

elem_biko_erregelak(_I).


gehitu_erroreak(R1, R2, R_emaitza):- 
	!, relax_packages(R1, R1_ps),
	relax_packages(R2, R2_ps),
	relax_level(R1, R_l),
	relax_level(R_emaitza, R_l),
	append(R1_ps, R2_ps, R3_ps),
	relax_packages(R_emaitza, R3_ps).



arku_berria(N1):-
	retract(arku_zenbakia(N)),
	N1 is N + 1,
	assert(arku_zenbakia(N1)).



info_arku(   arku(_ ,  _,   _,  _,     Info), Info).
has_arku(    arku(_ , Has,  _,  _,     _   ), Has).
buk_arku(    arku(_, _ ,  Buk,  _,     _   ), Buk).
egitura_arku(arku(_, _,   _,   Eg,     _   ), Eg).


erregela(info(R, _, _), R).

semeak(info(_R, [X, Y], _), X, Y).

semea(info(_R, [X], _), X).

arku_zenb(info(_R, _S, AZ), AZ).



%----------------------------------------------------------------------------
%
%	Top Level
%
%	This gets all parses from a given string.
%

%
%	 parses/1 and max_level/1
%
% There is an initial value max_relax/1 that is used to set the limit for 
% relaxations. parses/1 is simply the `interface' predicate that calls all
% the parsing processes that are required up to that level of relaxation.

relax_level(relax_record(X, _Y), X):-!.
relax_packages(relax_record(_X,Y), Y):-!.






% 2005-VI-30. 
kateatu_izena(FileInput, Luzapena, Izena):-
        name(FileInput, L1),
        name(Luzapena, L2),
        append(L1, L2, L3),
        name(Izena, L3).



% predikatu hau esaldi bat tratatzeko erabiliko da. Adib: ana("etorri da ."):

ana(Esaldia):-
	fitxategira_pasa(Esaldia, sint),
        (\+analizatu_sint -> (    nl, write('Esaldi hori ezin da analizatu '), nl, nl);
				(true)).

% Bertsio berria (2003-XII)
% Morfosintaxi berria XMLz
mana(Esaldia):- % morfologikoki analizatzeko
        sortu_morfsar(Esaldia, FIzena_morfsar),
        [FIzena_morfsar],
%       ['palkk.morfsar'],
	bilduta,
	hiztegia_hasieratu_morf, 
          % hiztegiko hitzak hasieratik ebaluatzen dira
 	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(1000000),
	osoak2.


sortu_morfsar(Esaldia, FIzena_morfsar):-
        atom_chars(FIzena, Esaldia),
	open(FIzena, write, F),
	kopiatu_katea(Esaldia, F),
        nl(F),
	close(F),
        ezabatu_charta,

        kateatu_izena('lemati.pl -xml -nodes ', FIzena, Lemati_Kom),
        shell(Lemati_Kom),
        kateatu_izena('/soft_ixa_solaris/bin/morfosintaxia_5 -a ', FIzena, Morf_Kom1),
        kateatu_izena(Morf_Kom1, ' -m TO_MORFSAR', Morf_Kom),
        shell(Morf_Kom),
        kateatu_izena( FIzena, '.morfsar', FIzena_morfsar).




mana_morfsar(Fmorfsar):- % morfologikoki analizatzeko
        ezabatu_charta,
	[Fmorfsar],
	bilduta,
	hiztegia_hasieratu_morf, 
          % hiztegiko hitzak hasieratik ebaluatzen dira
 	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(1000000),
	osoak2.





/*
% Bertsio zaharra: 2003-XII-2
mana(Esaldia):- % morfologikoki analizatzeko
	fitxategira_pasa(Esaldia, morf),
        (\+analizatu_morf -> (    nl, write('Esaldi hori ezin da analizatu '), nl, nl);
				(true)),
	osoak2.
*/

/*
mana_fitx(Hitzaren_fitxategi_izena):- % morfologikoki analizatzeko
	ezabatu_charta,
        kateatu_izena(Hitzaren_fitxategi_izena, '.sar', E_f_i_sar),
        kateatu_izena('$patr_morfo/prozesatu-morf.pl ', Hitzaren_fitxategi_izena, Kom1),
	shell(Kom1),
	% $patr_kbp/prozesatu-morf.pl esa -- emaitza esa.sar fitxategia
        analizatu_morf(E_f_i_sar).
*/


fitxategira_pasa(Esaldia, Sint_Morf):-
	open(palkk, write, F),
	kopiatu_katea(Esaldia, F),
	close(F),
 	((Sint_Morf = sint) -> shell('./prozesatu-sint '); % sicstus
                               shell('$patr_morfo/prozesatu-morfo')).
% 	((Sint_Morf = sint) -> unix(system('prozesatu-sint <sarrera1 >sarrera')); quintus
%                              unix(system('prozesatu-morf-sisa05 <sarrera1 >sarrera'))).
	

kopiatu_katea([], _F2).

kopiatu_katea([C|Y], F2):- 
	tratatu(F2, C),	
	kopiatu_katea(Y, F2).












% predikatu hau esaldien fitxategia tratatzeko erabiliko da:
% sarrerako fitxategi batetik esaldia irakurriko du, analizatuko du
% eta emaitza irt1 irteerako fitxategian idatzi

batch(F_sar_izena):-
	open(F_sar_izena, read, F_sar),
	tratatu_esaldiak(F_sar),
	close(F_sar),
	set_output(user_output).


tratatu_esaldiak(F_sar):-
	irakurri_esaldia(F_sar, Azkena),
	((Azkena = ez_azkena) -> (      kopiatu_f(sarrera1, xxx, 'ESALDIA'),
					open(irt1, write, I),
					set_output(I),
					(analizatu -> true ; 
					    (nl, write('EZ DAGO ANALISIRIK'), nl)),
					close(I),
					kopiatu_f(irt1, xxx, '   '),
					tratatu_esaldiak(F_sar));
				(true)).

irakurri_esaldia(F_sar, Azkena):-
	open(sarrera1, write, Irteera),
	kopiatu(F_sar, Irteera, Azkena),
	close(Irteera),
        shell('prozesatu-sint <sarrera1 >sarrera'). % sicstus	
      %  unix(system('prozesatu-sint <sarrera1 >sarrera')). quintus
	

kopiatu_f(N1, N2, Goiburukoa):-
	open(N1, read, F1),
	open(N2, append, F2),
        nl(F2), nl(F2),write(F2, Goiburukoa),
	kopiatu1_f(F1, F2),
	close(F1),
	close(F2).

kopiatu1_f(F1, _F2):-
	at_end_of_file(F1), !.

kopiatu1_f(F1, F2):- 
	get0(F1, C),
	tratatu(F2, C),	
	kopiatu1_f(F1, F2).

tratatu(F, C):-
	lerro_bukaera(C), nl(F), !.
tratatu(F, C):-
	put_id(F, C).
					
lerro_bukaera(10).	
	

put_id(C):- name(A, [C]), atom(A), write(A), !. % gidoia eta bezalakoak ez tratatzeko
put_id(C):- put(C).
% txapuza bat, bestela ASCII kodea idazten duelako


kopiatu(Sarrera, Irteera, Azkena):-
	get0(Sarrera, C),	
	kopiatu1(Sarrera, Irteera, C, Azkena).

kopiatu1(_Sarrera, _Irteera, C, azkena):- 
	dolarra(C), !.
% ez dago beste esaldirik


kopiatu1(Sarrera, Irteera, C, Azkena):- 
	lerro_bukaera(C), !, % lerro-bukaera pasa
	get0(Sarrera, C1),
	kopiatu1(Sarrera, Irteera, C1, Azkena).



kopiatu1(_Sarrera, Irteera, C, ez_azkena):- 
	bukaera(C), !, 
	put_id(Irteera, C), put_id(Irteera, 32), nl(Irteera). 
			% bukaeran zurigunea (32) jarri dut
% puntua irakurri bada, bukatu da esaldi hau, baina badaude beste esaldi batzuk

kopiatu1(Sarrera, Irteera, C, Azkena):-
	put_id(Irteera, C),
	get0(Sarrera, C1),
	kopiatu1(Sarrera, Irteera, C1, Azkena).


put_id(Irt, C):- name(A, [C]), atom(A), write(Irt, A). % gidoia eta bezalakoak ez tratatzeko
put_id(Irt, C):- put(Irt, C).
% txapuza bat, bestela ASCII kodea idazten duelako

bukaera(C):- name('.', [C]).
bukaera(C):- name('!', [C]).
bukaera(C):- name('?', [C]).
dolarra(C):- name('$', [C]).



analizatu_morf(Fitx):-
	banatuta,
	abolish(dict, 6),
	abolish(lexema, 4),
	ezabatu_arkuak,
	[Fitx], 
% fitxategi horretan utzi dira analisi morfologikoaren emaitzak
	hiztegia_hasieratu_morf, 
% hiztegiko hitzak hasieratik ebaluatzen dira
	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(1000000).




analizatu_morf:-
	banatuta,
	abolish(dict, 6),
	abolish(lexema, 4),
	ezabatu_arkuak,
	['sarrera'], 
% fitxategi horretan utzi dira analisi morfologikoaren emaitzak
	hiztegia_hasieratu_morf, 
% hiztegiko hitzak hasieratik ebaluatzen dira
	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(1000000).
	% parses.
% analisirik ez bada aurkitu ere, predikatua ez da beteko



/* Bertsio zaharra: 2000-10-26an baztertua

% predikatu honek anali-ren irteera duen fitxategi bat hartuta
% analisi guztien zerrenda lortuko du.
analizatu_morf_morfeus(Fitx_anali, An_lista):-
	bilduta,
	abolish(dict, 6),
	abolish(lexema, 4),
        % name('/sx0507/users/jirsint/sicstus/prozesatu-morf-morfeus', Kom_l),
        name('$morfeus_bin/prozesatu-morf-morfeus', Kom_l1),
        name(Fitx_anali, Fitx_anali_l),
	append(Fitx_anali_l, ".sar", F_Emaitza_Izena1),
	append(" >", F_Emaitza_Izena1, F_Emaitza_Izena2),
	append(" <", Fitx_anali_l, L1),
	append(Kom_l1, L1, Kom_l2),
	append(Kom_l2, F_Emaitza_Izena2, Kom_l3),
        name(Komandoa, Kom_l3),
	shell(Komandoa), % honek post1.kom, anali -> PATR eta post2.kom deitzen du
	ezabatu_arkuak,
	atom_chars(Sarrera, F_Emaitza_Izena1),
	[Sarrera], 
% fitxategi horretan utzi dira analisi morfologikoaren emaitzak
	hiztegia_hasieratu_morf, 
% hiztegiko hitzak hasieratik ebaluatzen dira
	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(1000000),
	parses_morfeus(1000000, An_lista).
%        idatzi_egiturak(An_lista).

% analisirik ez bada aurkitu ere, predikatua ez da beteko
*/

/*
% predikatu honek anali-ren irteera Prolog eran (dict(...)) duen fitxategi 
% bat hartuta analisi guztien zerrenda lortuko du.
kkk_analizatu_morf_morfeus_zaharra(Sarrera, An_lista):-
	ezabatu_charta,
	bilduta,
	[Sarrera],
	hiztegia_hasieratu_morf, 
          % hiztegiko hitzak hasieratik ebaluatzen dira
	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(1000000),
	parses_morfeus(1000000, An_lista).
          %        idatzi_egiturak(An_lista).

*/





% Identifikatzaileen zerrendak fitxategi batean idatziko dira, gero konparatu ahal izateko
idatzi_identifikatzaileak(Analisiak, Etiketak, FIzena):-
	open(FIzena, write, FIrt),
        idatzi_identifikatzaileak2(Analisiak, Etiketak, FIrt),
        close(FIrt).

idatzi_identifikatzaileak2([], [], _F):-!.
idatzi_identifikatzaileak2([[analisia(X) | _Besteak] | Best_An], [Etik_Zerrenda | Rest], F):-
        eval(X/forma, Z), write(F, Z), write(F, ': '),
        idatzi_lerroan(Etik_Zerrenda, F), nl(F),
        idatzi_identifikatzaileak2(Best_An, Rest, F).

idatzi_lerroan([], _F):-!.
idatzi_lerroan([Etik | Rest], F):-
        write(F, Etik), write(F, ' '),
        idatzi_lerroan(Rest, F).





% Probak modu elkarreragilean egiteko modu errazean, adib.: analizatu('amari.morfsar').
analizatu(Fitx) :- analizatu_morf_morfeus(Fitx, L), idatzi_egiturak(L).


% Berria. Aitziber eta Koldo 2001-XI-22
% Orain sarrerako fitxategiak hitz askoren analisiak izango ditu, bakoitza
%   "hitz_bukaera"-rekin amaituta.
% Hitz baten analisiak irakurriko dira eta memorian sartuko dira. Ondoren
% analizatuko da, gordeko da emaitza, eta gero ezabatu memoriatik eta beste
% hitz bat irakurri, ...
% predikatu honek anali-ren irteera Prolog eran (dict(...)) duen fitxategi 
% bat hartuta hitz guztien analisi guztien zerrenda lortuko du.
analizatu_morf_morfeus(Sarrera, An_lista, ID_l):-
	open(Sarrera, read, F_Sar),
	bilduta,
	tratatu_hitzak_eta_bueltatu_analisiak(F_Sar, An_lista, ID_l),
	close(F_Sar).

% lehengo bertsioarekin bateragarria izateko: id-en lista ez da kontuan hartzen
analizatu_morf_morfeus(Sarrera, An_lista) :-
	analizatu_morf_morfeus(Sarrera, An_lista, _ID_l).


% Sarrera: F_Sar-en hitz askoren analisi morfologikoak, 'hitz_bukaera'
%          terminoarekin banatuta, eta bukaeran 'fitxategi_bukaera' terminoa
% Irteera: An_Lista = [L1, L2, ..., Ln]
%          Li = i-garren hitzaren analisi morfosintaktikoa
tratatu_hitzak_eta_bueltatu_analisiak(F_Sar, An_lista, ID_lista):-
	ezabatu_charta,
	read(F_Sar, Term), % irakurri lehenengo terminoa
	irakurri_morfemak(F_Sar, Bukaera, Term, Hurrengo_Term),
        tratatu_hitzak_eta_bueltatu_analisiak2(F_Sar, An_lista, ID_lista, Bukaera, Hurrengo_Term, 1000000).


% bestela hitz bat tratatu, gehitu bere analisia eta jarraitu prozesua
tratatu_hitzak_eta_bueltatu_analisiak2(F_Sar,
				       [Analisiak | Besteak],
				       [ID_ak | Beste_ID_ak],
				       hitz_bukaera,
				       Aurreko_Terminoa,
				       Hitz_Zenbakia):-
	!,
	hiztegia_hasieratu_morf, 
          % hiztegiko hitzak hasieratik ebaluatzen dira
 	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(Hitz_Zenbakia),
	parses_morfeus(Hitz_Zenbakia, Analisiak, ID_ak), !,
        %          idatzi_egiturak(Analisiak).
	% ezabatu_charta,  % 14-IX-2004
	Hurrengo_Zenbakia is Hitz_Zenbakia + 1000000,
	ezabatu_charta,  % ????????????????
	irakurri_morfemak(F_Sar, Bukaera, Aurreko_Terminoa, Hurrengo_Terminoa),
	tratatu_hitzak_eta_bueltatu_analisiak2(F_Sar,
					       Besteak,
					       Beste_ID_ak,
					       Bukaera,
					       Hurrengo_Terminoa,
					       Hurrengo_Zenbakia).



% bestela fitxategiaren bukaera da
tratatu_hitzak_eta_bueltatu_analisiak2(_F_Sar,
				       [Analisiak],
				       [ID_ak],
				       end_of_file,
				       Aurreko_Terminoa,
				       Hitz_Zenbakia):-
	% arku_zenbakia(_U), % oraindik hitz bat dago tratatu gabe
	Aurreko_Terminoa \== end_of_file,
	!,
	hiztegia_hasieratu_morf, 
	retractall(arku_zenbakia(_)),
	assert(arku_zenbakia(0)),
	chart_hasieratu(Hitz_Zenbakia),
	parses_morfeus(Hitz_Zenbakia, Analisiak, ID_ak), !,
          %        idatzi_egiturak(Analisiak).
	% ezabatu_charta,   % 14-IX-2004
	!.

tratatu_hitzak_eta_bueltatu_analisiak2(_F_Sar,
				       [],
				       [],
				       end_of_file,
				       _Aurreko_Terminoa,
				       _Hitz_Zenbakia):-
	!.


irakurri_morfemak(_Fitx, Buk,  _Term, _Term):-
	nonvar(Buk),
	Buk = hitz_bukaera,
	!.

irakurri_morfemak(_Fitx, end_of_file,  end_of_file, _Hurrengo_Term):- !.
irakurri_morfemak(Fitx, Bukaera, Aurreko_Term, Hurrengo_Term):-
	assert(Aurreko_Term),
	read(Fitx, Term_Berria),
	bukaera_ala_ez(Aurreko_Term, Term_Berria, Bukaera),
	irakurri_morfemak(Fitx, Bukaera, Term_Berria, Hurrengo_Term).


zenbakia(dict(Hasiera, _Bukaera, _Bestea), Zenb):-
	Zenb is Hasiera // 1000000.

bukaera_ala_ez(_Term, end_of_file, end_of_file):- !.

bukaera_ala_ez(TermA, TermB, _):- % baliorik eman gabe jarraituko du
	zenbakia(TermA, Zenb),
	zenbakia(TermB, Zenb),
	!.
bukaera_ala_ez(TermA, TermB, hitz_bukaera):-
	zenbakia(TermA, ZenbA),
	zenbakia(TermB, ZenbB),
	ZenbB is ZenbA + 1,
	!.
           % beste hitz bat hasi da


/* 2002-IV-17an aldatuta Koldo
   % Orain ez dira egongo hitz_bukaera eta fitx_bukaera markak
irakurri_morfemak(Fitx, Bukaera):-
	read(Fitx, Term),
	irakurri_beste_morfemak(Fitx, Term, Bukaera).

irakurri_beste_morfemak(_Fitx, fitx_bukaera, fitx_bukaera):- !.
irakurri_beste_morfemak(_Fitx, hitz_bukaera, hitz_bukaera):- !.
irakurri_beste_morfemak(Fitx, Term, Bukaera):-
	assert(Term),
	read(Fitx, Term1),
	irakurri_beste_morfemak(Fitx, Term1, Bukaera).
*/

/* 14-IX-2004 aldatuta
ezabatu_charta:-
%	abolish(dict, 3),
	abolish(dict, 3),
	abolish(lexema, 4),
	abolish(arku, 5),
	ezabatu_atera_arku, % &&&&&&&&&
	ezabatu_iritsi_arku.
	% abolish(iritsi_arku, 3).
*/


ezabatu_charta:-
	retractall(dict(_,_,_)),
	retractall(lexema(_,_,_,_)),
	retractall(arku(_,_,_,_,_)),
	ezabatu_atera_arku, % &&&&&&&&&
	ezabatu_iritsi_arku.
	% abolish(iritsi_arku, 3).





analizatu_sint:-
	% retractall(dict, 6),
	% retractall(lexema, 4),
	retractall(dict(_,_,_,_,_,_)),
	retractall(lexema(_,_,_,_)),
	['sarrera'], 
% fitxategi horretan utzi dira analisi morfologikoaren emaitzak
	hiztegia_hasieratu_sint, 
% hiztegiko hitzak hasieratik ebaluatzen dira
	parses.

% analisirik ez bada aurkitu ere, predikatua ez da beteko


ezabatu_arkuak:-
	ezabatu_arku,
	ezabatu_atera_arku, % &&&&&&&&&
	ezabatu_iritsi_arku.

ezabatu_arku:- retractall(arku(_,_,_,_,_)), !.
ezabatu_arku.
ezabatu_atera_arku:- retractall(atera_arku(_,_,_)), !. % &&&&&&
ezabatu_atera_arku.
ezabatu_iritsi_arku:- retractall(iritsi_arku(_,_,_)), !.
ezabatu_iritsi_arku.


% Hitz_Zenbakia analisiaren hasierako hitzarena da: 1000000, 2000000, ...
parses_morfeus(Hitz_Zenbakia, An_l_post3, ID_l) :- 
	% azken_nodoa(AN),
	AN is Hitz_Zenbakia + 1000000,
	findall(Egitura, 
		arku_osoa(Hitz_Zenbakia, AN, Egitura), 
		An_l),
	post_erregela_aplikatu(An_l, An_l_post1, ID_l), 
	aldagaiak_eta_string_listak_kendu(An_l_post1, An_l_post2),
	analisiak_jarri_aurretik(An_l_post2, An_l_post3).

% Aingeruk nahiago du analisien lista bat ematea: analisiak:[analisia(...), analisia(...)...]




kkk(Hitz_Zenbakia, An_l_post1) :- 
	azken_nodoa(AN),
	findall(Egitura, 
		arku_osoa(Hitz_Zenbakia, AN, Egitura), 
		An_l),
	post_erregela_aplikatu(An_l, An_l_post1).




% Hitz_Zenbakia analisiaren hasierako hitzarena da: 1000000, 2000000, ...
parses_morfeus2(Hitz_Zenbakia, Analisien_Lista, Zenbakien_Lista) :- 
	azken_nodoa(AN),
	findall([Analisia, Zenbakia], 
		arku_osoa2(Hitz_Zenbakia, AN, Analisia, Zenbakia), 
		Analisien_eta_Zenbakien_Lista),
	banatu(Analisien_eta_Zenbakien_Lista, An_L, Zenbakien_Lista),
	post_erregela_aplikatu(An_L, An_l_post1, _Id_l),
	aldagaiak_eta_string_listak_kendu(An_l_post1, An_l_post2),
	% reverse(An_l_post2, An_l_post3), % analisiak alderantzizko ordenan jarri dira: bueltatu
	analisiak_jarri_aurretik(An_l_post2, Analisien_Lista).




arku_osoa(Hitz_Zenbakia, AN, Egitura):-
	iritsi_arku(AN, Hitz_Zenbakia,  Zenb),
        arku(Zenb, Hitz_Zenbakia,  AN, [_Kat, Egitura], _Info).


% aurrekoaren berdina, baina orain zenbakia bueltatzen du
arku_osoa2(Hitz_Zenbakia, AN, Egitura, Zenb):-
	iritsi_arku(AN, Hitz_Zenbakia,  Zenb),
        arku(Zenb, Hitz_Zenbakia,  AN, [_Kat, Egitura], _Info).




banatu([], [], []).
banatu([[An, Zenb]| Besteak], [An | Beste_Analisiak], [Zenb | Beste_Zenbakiak]):-
	banatu(Besteak, Beste_Analisiak, Beste_Zenbakiak).



% sarrera analisien lista
% irteerak: analisen lista potprozesuarekin, id-en lista
post_erregela_aplikatu([], [], []).

post_erregela_aplikatu([Egitura | Besteak], [Egitura_irt | Besteak_irt], [ID | Beste_IDak]):-
%        banatu_ezaugarriak(Egitura, Egitura_irt), posttratamenduaren erregela 
%         aplikatu elementuei
	rule_post(_Kat, erregela_post, Egitura_irt, [Egitura]),
	id_a_lortu(Egitura, ID),
	post_erregela_aplikatu(Besteak, Besteak_irt, Beste_IDak),
	!.


id_a_lortu(Egitura, ID):-
	solve([m(_, Egitura/id definitua)]), % definitua baldin badago, orduan hartu
	!,
	solve([m(_, Egitura/id <=> ID1)]),
	name(ID, ID1).

%id_a_lortu(_Egitura, 'KKK').   % bestela sortu edozein gauza.
id_a_lortu(Egitura, 'KKK'):- nl, write('********** id-rik ez du!'), solve([m(_, Egitura/forma <=> Forma)]), aztertu_eta_idatzi(Forma), nl. 





analisiak_jarri_aurretik([], []):- !.
analisiak_jarri_aurretik([X|Y], [analisia(X)|Bestea]):-
	!,
	analisiak_jarri_aurretik(Y, Bestea).





% predikatu honek aldagai hutsak kenduko ditu ezaugarri-egituretatik, adibidez:
%              [biz:_, _]
%              [oin:[biz:_, neur:_, _],_]
% gainera, zenbakien lista bezala ematen diren stringetan, katea emango du, adib.:
%        [102, 103, 105, 104] -> "e_em"

aldagaiak_eta_string_listak_kendu([], []):-!.

aldagaiak_eta_string_listak_kendu([An1|Besteak], [AnBerria|BesteakBerri]):-
	kendu_aldagaiak_eta_stringak_analisitik(An1, AnBerria),
	!,
	aldagaiak_eta_string_listak_kendu(Besteak, BesteakBerri).
	

kendu_aldagaiak_eta_stringak_analisitik(Balioa, Balioa):-
	atom(Balioa),
	!.

kendu_aldagaiak_eta_stringak_analisitik(Balioa, Balioa):-
	number(Balioa), % "0"ak
	!.

% [100, 102, ...] moduko listak, adib.: "forma", string bihurtuko dira
kendu_aldagaiak_eta_stringak_analisitik([N|Rest], Balioa):-
	number(N),
	!,
%	name(Balioa, [N|Rest]). 
	atom_codes(Balioa, [N|Rest]). 

/*
kendu_aldagaiak_eta_stringak_analisitik(L, L2):-
	L = [fs(_)|_],
	kendu_stringak_fsl(L, L2),
	!.
*/

kendu_aldagaiak_eta_stringak_analisitik(L, L2):-
	L = [[N|_Rest]|_],
        number(N),   % hau da, lista bat bada, orduan funtzio sintaktikoak dira
	kendu_stringak_fsl(L, L2),
	!.


kendu_aldagaiak_eta_stringak_analisitik(L, L2):-
	L = [morf(_)|_],
	kendu_aldagaiak_eta_stringak_morf_lista(L, L2),
	!.

kendu_aldagaiak_eta_stringak_analisitik(L, L2):-
	L = ['Gako'(_)|_],
	kendu_aldagaiak_eta_stringak_gako_lista(L, L2),
	!.

kendu_aldagaiak_eta_stringak_analisitik(L, L2):-
	L = [osagaia(_)|_],
	kendu_aldagaiak_eta_stringak_osagai_lista(L, L2),
	!.


kendu_stringak_fsl([], []):-!.
kendu_stringak_fsl([B|Besteak], [BBerri|BesteakBerri]):-
	!,
	name(BBerri, B),
	kendu_stringak_fsl(Besteak, BesteakBerri).
				       
kendu_aldagaiak_eta_stringak_morf_lista([], []):-!.
kendu_aldagaiak_eta_stringak_morf_lista([morf(M)|Besteak], [morf(MBerri)|BesteakBerri]):-
	!,
	kendu_aldagaiak_eta_stringak_analisitik(M, MBerri),
	kendu_aldagaiak_eta_stringak_morf_lista(Besteak, BesteakBerri).

% ['Gako'(), 'Gako'(B), ...] orain arte erabili da, baina emaitzan ez da behar: [A, B, ...]
% beraz, pauso honetan desagertuko da
kendu_aldagaiak_eta_stringak_gako_lista([], []):-!.
kendu_aldagaiak_eta_stringak_gako_lista(['Gako'(G)|Besteak], ['Gako'(GBerri)|BesteakBerri]):-
	!,
	kendu_aldagaiak_eta_stringak_analisitik(G, GBerri),
	kendu_aldagaiak_eta_stringak_gako_lista(Besteak, BesteakBerri).
				       
kendu_aldagaiak_eta_stringak_osagai_lista([], []):-!.
kendu_aldagaiak_eta_stringak_osagai_lista([osagaia(O)|Besteak], [osagaia(OBerri)|BesteakBerri]):-
	!,
	kendu_aldagaiak_eta_stringak_analisitik(O, OBerri),
	kendu_aldagaiak_eta_stringak_osagai_lista(Besteak, BesteakBerri).
				       
	



kendu_aldagaiak_eta_stringak_analisitik(An1, AnBerria):-
	kendu_aldagaiak_eta_stringak_analisitik(An1, [], AnBerria).

% listak beti aldagai batekin bukatzen dira
kendu_aldagaiak_eta_stringak_analisitik([_Ezaug:Balioa|Y], Azkena, Azkena):-
	denak_aldagaiak(Balioa),
	var(Y),
	!.

kendu_aldagaiak_eta_stringak_analisitik(Y, Azkena, Azkena):-
	var(Y),
	!.

kendu_aldagaiak_eta_stringak_analisitik([_Ezaug:Balioa|Besteak], Aurrekoa, Azkena):-
	denak_aldagaiak(Balioa), % Besteak ez da aldagaia
	!,
	kendu_aldagaiak_eta_stringak_analisitik(Besteak, Aurrekoa, Azkena).
	
/*
kendu_aldagaiak_eta_stringak_analisitik_EH([EE|Besteak], Aurrekoa, Azkena):- % 2005-V-24 hobetsiak/estandarrak
	!,
	kendu_aldagaiak_eta_stringak_analisitik(EE, EEGarbia),
	append(Aurrekoa, EEGarbia, Aurrekoa2),
	kendu_aldagaiak_eta_stringak_analisitik_EH(Besteak, Aurrekoa2, Azkena).

kendu_aldagaiak_eta_stringak_analisitik_EH([], Azkena, Azkena):- % 2005-V-24 hobetsiak/estandarrak, kasu sinplea
	!.



kendu_aldagaiak_eta_stringak_analisitik([Ezaug:Balioa_EH | Besteak], Aurrekoa, Azkena):- % 2005-V-24 EH1, EH2
	estandarrak_edo_hobetsiak(Ezaug),
	!,
	% "Ezaug" ezaugarria estandarra edo hobetsia da, kasu berezia
	kendu_aldagaiak_eta_stringak_analisitik_EH(Balioa_EH, [], BalioGarbia_EH),
	append(Aurrekoa, [Ezaug:BalioGarbia_EH], Aurrekoa2),
	kendu_aldagaiak_eta_stringak_analisitik(Besteak, Aurrekoa2, Azkena).

estandarrak_edo_hobetsiak(estandarrak) :-!.
estandarrak_edo_hobetsiak(hobetsiak)   :-!.
*/

kendu_aldagaiak_eta_stringak_analisitik([Ezaug:Balioa|Besteak], Aurrekoa, Azkena):-
	% "Ezaug" ezaugarriak badauka zerbait aldagaia ez dena, beraz mantenduko da
	kendu_aldagaiak_eta_stringak_analisitik(Balioa, BalioGarbia),
	append(Aurrekoa, [Ezaug:BalioGarbia], Aurrekoa2),
	kendu_aldagaiak_eta_stringak_analisitik(Besteak, Aurrekoa2, Azkena).



				 
max_relax(0).


idatzi_esaldia([]):- nl.
idatzi_esaldia([X|Rest]):-
	write(X), write(' '),
	idatzi_esaldia(Rest).
	
	


	
analisiak_idatzi(P) :-
	analisiak_kontatu(P, An_kop),
	nl, write('analisi-kopurua '), write(An_kop),nl,nl,
	((Err_kop_min = 0) -> true;
                         (nl, write('errore-kopuru minimoa: '), write(Err_kop_min), nl)),
        open('osagaiak.pl', append, Fitx),
	anal_minimoak_idatzi(Fitx, P, 0),
        close(Fitx).
	% idatzi_erroreak(Errore_kopuruen_lista).

analisiak_kontatu(P, An_kop) :-
	analisiak_kontatu1(P, 0, An_kop).

analisiak_kontatu1([], X, X).
analisiak_kontatu1([[]|_], X, X).
analisiak_kontatu1([_Bat | Rest], Kop, Kopazk) :-
	Kop2 is Kop + 1,
	% erroreak(Relax_record, Erroreak),
	% ((Erroreak < Min, !, Min2 is Erroreak);
	% (Min2 is Min)),
	analisiak_kontatu1(Rest, Kop2, Kopazk).


erroreak(relax_record(_, Relax_packages), Erroreak):-
	erroreak1(Relax_packages, 0, Erroreak).
erroreak1([], Err, Err).
erroreak1([_R|Rs], Err1, Errazk):-
	erroreak1(Rs, Err1, Err2),
	Errazk is Err2 + 1.


anal_minimoak_idatzi(_Fitx, [], _E):- !.
anal_minimoak_idatzi(_Fitx, [[]|_], _E):- !.
anal_minimoak_idatzi(Fitx, [Arku|Rest], Err_kop_min):-
	% erroreak(Relax_record, Err_kop_min), !,
	Arku = arku(_N1, _N2, [_Kat, _Eg], info(_E, _F,_N)),
	% ppc(Eg),nl,nl,
        portray_clause(Fitx, Arku), 
	% printrelax(Relax_record),
	anal_minimoak_idatzi(Fitx, Rest, Err_kop_min).
	% gehitu(Err_kop_min, Err_lista1, Err_lista).	
% errore-kopuru minimoa badu, orduan idatzi hau eta segi

anal_minimoak_idatzi([[_Parse|Relax_record]|Rest], Err_kop_min, Err_lista):-
	erroreak(Relax_record, Erroreak),
	anal_minimoak_idatzi(Rest, Err_kop_min, Err_lista1),
	gehitu(Erroreak, Err_lista1, Err_lista).	
% bestela besteekin segi

gehitu(Kop, [[Kop, Z]|Rest], [[Kop, Zberria]|Rest]):- 
	Zberria is Z + 1, !.
gehitu(K, [[Kop, Z]|Rest], [[Kop, Z]|Rest1]):-
	gehitu(K, Rest, Rest1).
gehitu(Kop, [], [[Kop, 1]]).




idatzi_erroreak([]).
idatzi_erroreak([[Kop, Z]|Rest]):-
        nl, write('***'),
	(Kop = 0 -> true;
                    (nl, write('Errore-kopurua: '), write(Kop), write(' '), write(Z), nl)),
	idatzi_erroreak(Rest).


printparses([]).
printparses([[]|_]).
printparses([[Parse|_Relax_record]|Rest]):-
	ppc(Parse), !, 
	% printrelax(Relax_record),
	printparses(Rest).

printrelax(relax_record(_, [])):-
	nl, write('///'), 
	% write('Ez da murriztapenik kendu. '),
	 nl.
printrelax(relax_record(_, Relax_packages)):-
	write('///'), nl,
	write('Errore posiblea(k):'),nl,
	write('///'), nl,
	print_relax_packages(Relax_packages), nl.

print_relax_packages([]):-!.
print_relax_packages([R|Rs]):-
	print_relax_package(R),nl,print_relax_packages(Rs).

print_relax_package(R):-
	error_message(R, S),nl, name(Message,S),
	write(Message),nl.
%	write('Kendutako murriztapenak:'),nl,nl,
%	relaxed_constraints(R, C),
%	print_constraints(C).
	
	
print_constraints([]).
print_constraints([m(_I, LHS <=> RHS)|Constraints]):-
	write(LHS),nl,write('<=>'),nl, write(RHS),nl,
	print_constraints(Constraints).

printdags([]).

printdags([[]|_]).

printdags([First|Rest]):-
	ppc(First),
	nl,
	printdags(Rest).

%
%----------------------------------------------------------------------------



%----------------------------------------------------------------------------
%
%	PATR in Prolog:	graph_unification.p
%	
%	Author:		Robert Dale (R.Dale@uk.ac.edinburgh)
%	Revisions:	Shona Douglas (S.Douglas@uk.ac.edinburgh) 
%	Date:		Tuesday 3rd September 1991
%	Notes:		This used to be part of the series of files
%			patr0912.p---patr0921.p

%----------------------------------------------------------------------------
%
%	Graph Unification Predicates
%
%----------------------------------------------------------------------------


%
%	unify(Graph, Graph)
%
 
% This predicate takes two graphs and tries to unify them.
% See the detailed description in "Notes on Graph Unification".

unify(X,X):- !.
unify([Attribute:Value1|Rest1], F2):-
        del(Attribute:Value2, F2, Rest2),
        unify(Value1, Value2),
        unify(Rest1, Rest2).

% del/3
%
% Given an element and a list, returns the list minus that element.

del(F, [F|X], X):- !.
del(F, [E|X], [E|Y]):-
        del(F, X, Y).




% Analizatzailearen emaitza ikusteko predikatuak
% predikatu hau gaindituta geratu da, osoak2 egin eta gero
% honek 
osoak:- idatzi_arku_osoak.

idatzi_arku_osoak:-
	azken_nodoa(ND),
	iritsi_arku(ND, 1000000, Zenb),
	% arku(Zenb, 10000, ND, _A,  _Info),
	idatzi_arkua(Zenb), nl, nl,
	fail.

idatzi_arku_osoak.


osoak2:- parses_morfeus2(1000000, L, Zenbakien_Lista),
	   % "parses_morfeus"-ek egituren lista lortzen du (morfosintaxia)
	   % baina emaitzak ikusteko arku_zenbakiak ere nahi ditugu
	 idatzi_egiturak2(L, Zenbakien_Lista).

idatzi_egiturak([]):-!.

idatzi_egiturak([Eg|Besteak]):-
	nl, nl,
	ppc(Eg), nl, nl,nl,nl,
	idatzi_egiturak(Besteak),
	!.


idatzi_egiturak2([], []):-!.

idatzi_egiturak2([Eg|Besteak], [Zenb|Beste_Zenbakiak]):-
	nl, nl,
	ppc(Eg), nl, nl,nl,nl,
	print('Arku-zenbakia: '), print(Zenb),
	idatzi_egiturak2(Besteak, Beste_Zenbakiak),
	!.




arku(N) :- idatzi_arkua(N).

idatzi_arkua(N) :-
	arku(_Zenb, N1, N2, [_Kat, Eg], info(E, F,N)),
	print(N1), nl,
	print(N2), nl,
	ppc(Eg), nl,
	print(info(E,F,N)).


idatzi_erlajazioak([]):- !.

idatzi_erlajazioak(R) :- 
	relax_packages(R, P), 
	listatu(P).

listatu([]).

listatu([X|Y]) :-
	print(X), nl,
	listatu(Y).
 
% hau arku bat sortu duten erregelak idazteko erabiliko da
idatzi_erregelak(Arkua):- idatzi_erregelak(Arkua, 0).

idatzi_erregelak(Arkua, Tab) :-
	arku(_N1, _N2, [_Kat, _Eg], info(0, 0, Arkua)),
	tabs(Tab).



% predikatu honek i-tik j-raino hartzen duten arkuak idatziko ditu
arkuak_i_j(I, J) :- 
	I1 is I * 1000000,
	J1 is J * 1000000,
	foreach(arku(Zenb, I1, J1, [_Kat, Eg], info(E, F, N)),
		(nl, nl, ppc(Eg), print(info(E,F,N)), print(Zenb))).

% berdina, baina honetan morfema mailan
arkuak_i_j(IHitza, IMorfema, JHitza, JMorfema) :- 
	foreach(arku(nodo(IHitza,_IA,IMorfema), nodo(JHitza,_JA,JMorfema), [_Kat, Eg], info(E, F, N)),
		(ppc(Eg), print(info(E,F,N)), nl)).


% arku baten semeak ateratzeko
semeak(I) :- 
	arku(_zenb, _Nodoa, _ND, _A, info(Erreg, Semeak, I)),
	semeak_idatzi(0, Erreg, Semeak, I).

semeak_idatzi(Tab, _Erreg, [0], I) :-
	!, tabs(Tab),
	print(I), nl.


semeak_idatzi(Tab, Erreg, [J], I) :-
	tabs(Tab),
	print(I), print(' '),
	print(Erreg), nl, 
	arku(J, _Nodoa, _ND, _A, info(E, F, J)),
	Tabberri is Tab + 4,
	semeak_idatzi(Tabberri, E, F, J).

semeak_idatzi(Tab, Erreg, [J, K], I) :-
	tabs(Tab),
	print(I), print(' '),
	print(Erreg), nl, 
	arku(J, _Nodoa, _ND, _A, info(E1, F1, J)),
	Tabberri is Tab + 4,
	semeak_idatzi(Tabberri, E1, F1, J),
	arku(K, _, _, _, info(E2, F2, K)),
	semeak_idatzi(Tabberri, E2, F2, K).


idatzi_katea(K):- atom(K), !, print(K).
idatzi_katea(K):- ascii_lista_idatzi(K).



% arku baten umeak ateratzeko. Bertsio berria (2002ko martxoa)
umeak(I) :-
	nl,
	arku(_zenb, _Nodoa, _ND, [Kat, Eg], info(Erreg, Semeak, I)),
        solve([m(_, Eg/twolt <=> Sar)]),
	umeak_idatzi(0, Kat, Sar, Erreg, Semeak, I).

umeak_idatzi(Tab, Kat, Sar, _Erreg, [0], I) :-
	!, tabs(Tab),
        idatzi_katea(Kat),
	% print(Kat), 
	print(' ('), idatzi_katea(Sar), print(', '), print(I), print(')'), nl.


umeak_idatzi(Tab, Kat, Sar, Erreg, [J], I) :-
	tabs(Tab),
	idatzi_katea(Kat), print(' '),
%	print(Kat), print(' '),
	print(' ('), idatzi_katea(Sar), print(', '), print(Erreg), 
	print(', '), print(I), print(')'), print(' '),
	nl,
	arku(J, _Nodoa, _ND, [Kat2, Eg], info(E, F, J)),
        solve([m(_, Eg/twolt <=> Sar2)]),
	Tabberri is Tab + 6,
	umeak_idatzi(Tabberri, Kat2, Sar2, E, F, J).

umeak_idatzi(Tab, Kat, Sar, Erreg, [J, K], I) :-
	tabs(Tab),
	idatzi_katea(Kat), print(' '),
%	print(Kat), print(' '),
	print(' ('), idatzi_katea(Sar), print(', '), print(Erreg), 
	print(', '), print(I), print(')'), print(' '),
	nl,
	arku(J, _Nodoa, _ND, [Kat2, Eg2], info(E1, F1, J)),
        solve([m(_, Eg2/twolt <=> Sar2)]),
	Tabberri is Tab + 6,
	umeak_idatzi(Tabberri, Kat2, Sar2, E1, F1, J),
	arku(K, _,      _,   [Kat3, Eg3], info(E2, F2, K)),
        solve([m(_, Eg3/twolt <=> Sar3)]),
	umeak_idatzi(Tabberri, Kat3, Sar3, E2, F2, K).





aplikatu(AZ1, AZ2, Erreg_izena) :-
	arku(AZ1, _V0, _V1, [Kat1, Egitura1], info(_, _, AZ1)),
	arku(AZ2, _V3, _V4, [_Kat2, Egitura2], info(_, _, AZ2)),
	copy(Egitura1, Egitura1k),
	copy(Egitura2, Egitura2k),
	erregela_aplikatu(Kat1, Erreg_izena, _LHS, [Egitura1k, Egitura2k]).
% predikatu hau erregela bat bi nodori aplikatzen saiatzeko da, erroreak asmatzeko
aplikatu(AZ1, Erreg_izena) :-
	arku(AZ1, _V0, _V1, [Kat1, Egitura1], info(_, _, AZ1)),
	copy(Egitura1, Egitura1k),
	erregela_aplikatu(Kat1, Erreg_izena, _LHS, [Egitura1k]).
% predikatu hau erregela bat nodo bati aplikatzen saiatzeko da, erroreak asmatzeko


hasi :- ['hassint.pl'].



laguntza :-
	write('hauek dira predikatu lagungarriak: '),nl,nl,
	write('idatzi_arkua(N) (arku): arkuaren informazioa idazten du'),nl,nl,
	write('arkuak_i_j(i,j): i eta j-ren arteko arkuak idatziko ditu'),nl,nl,
	write('arkuak_i_j(i, m1 ,j, m2): i eta j-ren arteko arkuak idatziko ditu, '), nl, 
        write('    morfemak ere kontutan hartuta, hau da i-garren hitza, m1-garren morfema'),nl,nl,
	write('semeak(i): arku-zenbaki bat emanda, bere semeak agertuko dira zuhaitz-eran'),nl,nl,
	write('aplikatu(i,j,Erreg_izena): i, j chart-eko osagaiak lotzen saiatzen da '), nl,
        write(' erregela horrekin. Debuger-arekin erabiltzeko'),nl,nl,
	write('aplikatu(i,Erreg_izena): i chart-eko osagaia lotzen saiatzen da '), nl,
	write('ana("ikusi dut .") mana("etxea"): esaldi bat sintaktikoki/morfologikoki analizatzeko '),nl,nl,
	write('bilatu(isk) / idatzi_kat(isk): isk kategoriakoak diren arku-zenbaki guztiak emango ditu'),nl,nl,
	write('arku_zenbakia(A): arku-kopurua ematen du'), nl, nl, nl, nl.



bilatu(Kat):- arku(_, _, _, [_, [kat:Kat|_]], info(_,_,Em)), write(Em), write(' '), fail.
bilatu(_Kat):- !.

idatzi_kat(Kat):- arku(_, _, _, [_, [kat:Kat|_]], info(_,_,Em)), arku(Em), fail.
idatzi_kat(_Kat):- !.


% proba bat egiteko, lista bateko osagai guztiak idazteko
idatzi_l([]).
idatzi_l([A|B]):-
	print(A), nl, nl,
	idatzi_l(B).

