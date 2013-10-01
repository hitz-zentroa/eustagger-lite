:- multifile (rule/2), (relax_spec/4).

/* erregela honek ezaugarriak multzoetan banatuko ditu */

rule_lex(erregela_lexikoa, X0 ---> [X1]@[
                 m(1,  X0/oina/ezaug/kat                <=> X1/kat),
                 m(2,  X0/oina/ezaug/azp                <=> X1/azp),
                 m(3,  X0/oina/ezaug/adm                <=> X1/adm),
                 m(5,  X0/oina/ezaug/erl                <=> X1/erl),
                 m(6,  X0/oina/ezaug/mug                <=> X1/mug),
                 m(7,  X0/oina/ezaug/num                <=> X1/num),
                 m(8,  X0/oina/ezaug/kas                <=> X1/kas),
                 m(8,  X0/id                            <=> X1/id),  % ID berezia da. Irteerako ezaugarri-egituran ez da behar, baina bai eman beharko da irteeran!
                 m(9,  X0/oina/ezaug/fsl                <=> sortu_fsl(X1)),
                 m(9,  X0/oina/ezaug/hobetsiak          <=> sortu_hobetsiak_estandarrak_lista(hobetsiak,   X1, 'Gako')), 
                 m(9,  X0/oina/ezaug/estandarrak        <=> sortu_hobetsiak_estandarrak_lista(estandarrak, X1, 'Gako')), 

		 m(10, X0/forma                         <=> X1/forma),
		
                 m(11, X0/oina/ezaug/biz                <=> X1/biz),
                 m(12, X0/oina/ezaug/zenb               <=> X1/zenb),
                 m(13, X0/oina/ezaug/neur               <=> X1/neur),
                 m(14, X0/oina/ezaug/per                <=> X1/per),
                 m(15, X0/oina/ezaug/plu                <=> X1/plu),
                 m(16, X0/oina/ezaug/grm                <=> X1/grm),
                 m(17, X0/oina/ezaug/mdn                <=> X1/mdn),
                 m(17, X0/oina/ezaug/asp                <=> X1/asp),  
                 m(17, X0/oina/ezaug/mod                <=> X1/mod), 
                 m(17, X0/oina/ezaug/hit                <=> X1/hit), 
                 m(17, X0/oina/ezaug/klm                <=> X1/klm), 
                 m(17, X0/oina/ezaug/lagm               <=> X1/lagm),
                 m(17, X0/oina/ezaug/nmg                <=> X1/nmg), 
                 m(17, X0/oina/ezaug/adbm               <=> X1/adbm),
                 m(17, X0/oina/ezaug/'error-kode'       <=> X1/'error-kode'), 

                 m(18, X0/oina/ezaug/nor                <=> X1/nor),
                 m(19, X0/oina/ezaug/nori               <=> X1/nori),
                 m(20, X0/oina/ezaug/nork               <=> X1/nork),
                 m(21, X0/oina/ezaug/err/'Sarrera'      <=> X1/err/sarrera),
                 m(21, X0/oina/ezaug/err/'homografo-id' <=> X1/err/'homografo-id'),
                 m(22, X0/oina/ezaug/mdl                <=> X1/mdl),
                 m(23, X0/oina/ezaug/adoin              <=> X1/adoin), 
                 m(23, X0/oina/ezaug/mai                <=> X1/mai), 
                 m(24, X0/oina/ezaug/erakat             <=> X1/erakat),
                 m(25, X0/oina/ezaug/eraazp             <=> X1/eraazp),
                 m(25, X0/oina/ezaug/izaur              <=> X1/izaur),
                 m(26, X0/oina/ezaug/rare               <=> X1/rare),
                 m(26, X0/oina/ezaug/adz/'Sarrera'      <=> X1/adz/sarrera), 
                 m(26, X0/oina/ezaug/adz/'homografo-id' <=> X1/adz/'homografo-id'), 

                 m(26, X0/oina/ezaug/osa1/'Sarrera'         <=> X1/osa1/sarrera),        
                 m(26, X0/oina/ezaug/osa1/'homografo-id'    <=> X1/osa1/'homografo-id'), 
                 m(26, X0/oina/ezaug/osa2/'Sarrera'         <=> X1/osa2/sarrera),        
                 m(26, X0/oina/ezaug/osa2/'homografo-id'    <=> X1/osa2/'homografo-id'), 
                 m(26, X0/oina/ezaug/mtkat        <=> X1/mtkat),

                 m(26, X0/erat                    <=> '-'), % hau morfosintaxiaren barne-funtzionamendurako erabiliko da, jakiteko ea
					 % forma batek eratorpena duen ala ez
					 % Hau garrantzitsua da lema_osatua emateko orduan, jakiteko ea 2 mailatako forma 
                                         %  eman behar den edo sarrera arruntak
					 % 2 mailatako formak gero sorkuntza egiteko beharrezkoak izango dira
 
                 m(27, X0/ezaug                   <=> X0/oina/ezaug),
                 m(28, X0/twolt                   <=> X1/twol), % Koldok asmatuta, twol da baina ez da erabiliko azken emaitzean
					                        % hitz-forma osatzen duten osagaien twol ezaugarrien kateaketa,
					                        %   adib.: beR+egiN+te
					                        % eratorpenean erabilgarria izango da, twol kateen kateaketa delako
                 m(28, edo([eta([edo([X1/kat              badago [dek, amm, asp, erl, gra, eli],
				      X1/sarrera          badago ["ba"]  
				     ]), % "ba" kasu berezia da: partikulak (prt) beti lemak dira "ba" izan ezik
			         X0/oina/twol                   <=> X1/twol,
			         X0/oina/sarrera/'Sarrera'      <=> X1/sarrera,
			         X0/oina/sarrera/'homografo-id' <=> X1/'homografo-id',
			         Morfema_bat/ezaug              <=> X0/oina/ezaug,
			         Morfema_bat/twol               <=> X0/oina/twol, 
		                 Morfema_bat/sarrera            <=> X0/oina/sarrera,
			         Morfema_bat/twolt              <=> X0/twolt,
                                 edo([eta[X1/forma              <=> "bait",
                                          X0/lema_osatua        <=> X1/sarrera 
                                                   % nahiz eta lema ez izan, kasu honetan lema_osatua jarriko da!
                                         ],
                                      X0/forma <=> X0/forma  % zeozer jartzearren!!!
                                     ]),
		                 X0/morf_lista                  <=> [morf(Morfema_bat)]
			        ]),
			    % oinarrizko morfemen lista, elementu bakarrekoa
			    % gero hauek konposatu egingo dira
			   eta([X1/kat          ez    [dek, amm, asp, erl, gra, eli ],
				X1/sarrera      ez    ["ba"],    
			        X0/oina/twol    <=>        X1/twol,
                                edo[eta[X1/err/sarrera    definitua,    % aditza baldin bada, adib.: "noa" orduan lema "joan" da!
                                        X0/lema_osatua    <=>        X1/err/sarrera],
                                    eta[X1/adoin          definitua,
                                        X0/lema_osatua    <=>        X1/sarrera],  % edo "adoin"?
                                    X0/lema_osatua        <=>        X1/sarrera],  % azken aukera
				X0/oina/sarrera/'Sarrera'      <=> X1/sarrera,    
				X0/oina/sarrera/'homografo-id' <=> X1/'homografo-id',
				X0/lema_osatua_twol            <=> X1/twol
                                                      % 2 lema_osatua erabiliko ditut: bata forma "normalentzat"
			                              % eta bestea eratorpena + elkarketa dagoenerako (2 mailatako forma)
			       ])
			   ])
		  ),
                 m(2, edo( [eta[X1/aldaera definitua,
                                 edo[eta[X1/err/sarrera   definitua,    % aditza baldin bada, adib.: "nihoa" orduan aldaera "joan" da!
                                          X0/aldaera_osatua <=>        X1/err/sarrera],
                                      X0/aldaera_osatua     <=>        X1/aldaera  % azken aukera
                                    ]
                               ],             
                           X0/aldaera_osatua <=> ""    % aldaerarik ez badu, orduan kate hutsa jarriko dugu
                           
                 ]))
              ]
	).



gune(ezaug, [kas, biz, zenb, neur,     % 2004-XII-23 "num" eta "mug" kendu dut, batzuetan gaizki goratzen delako,
	                               % adib.: aren(num s) + 0(kas mg)
		  fsl, per, plu,
                  % adm kenduko dut, bestela kasu batzuetan goratzen da behar ez denean, 
                  % adibidez: eduki + tasun (eratorpena da, eta kasu horretan adm:part ez da goratu behar!
	          mdn, asp, nor, nori, nork, adoin, 
                  grm, mod, hit, klm, lagm, adbm, 'error-kode',
	          err, mdl, mai, izaur, rare,                   % erl, erlatz,
		  erat,                                         % "oin" "atzl" ezin dira sartu, bestela hitz-elkarketan
		                                                % "handitasun-egile" goratu egiten direlako, eta ez dagozkio "egile"ri
	          erat_atz,                                     % azken hau jakiteko ea atzizkia duen ala ez (r_eratorpena_aur)
		                                                % mugkz, mugtz,  % kenduta  2005-VI-6
	          elkarketa, elk, osa1, osa2,                   % hitz-elkarketan
                  adz, hobetsiak, estandarrak, mtkat            % 2005-V-20 Ezaugarri berriak ere goratzeko
                  ]).

% gune ez direnak: kat, azp, ker, aer, oin, atzl, forma, ...

/* Aurreko ezaugarriei nik asmatutako printzipio bat aplikatuko zaie:
   Erregela bitarretan:
    - beren balioak amarengan ez badaude orduan
    - beren balioak eskubiko elementutik hartuko dira
    - ez badaude, orduan ezkerreko elementutik
   Ezaugarriak /ezaug bidean daude
*/




% Erregela honek aurreko erregelen bidez lortutako knmdek hori kategoria nagusiekin 
% lotzen du. Ez da tratatuko elipsia gertatzen den kasua (horregatik baldintza batean eskatzen 
% da kasua ez izatea gen edo gel).

% ize/adj/det/ior/adi-part--> ize/adjdet/ior/adi-part + knmdek
% gizon+a, gizon+ari, gizon+arentzat, mendi+etara, mendi+etaraino, mendi+ko
% gizon+aren, gizon+arengana, gizon+arenganantz, gizon+agana
% gorri+etaraino
% makurtu+a, eman+arekin
% zenbait+engana
% ni+ri, zu+rekin
% eli(psia)+a
% determinatzaile zehaztuak ("bat" kenduta),  
% izen bereziak eta leku izen bereziak aparte tratatuko dira

rule(r_lehen_knmdek_arrunta, X0 ---> [X1, X2]@[
                 m(1, edo [eta [X1/ezaug/kat      badago [ize, ior, adj, det, eli, adb,
                                                          snb,
							  bst],	% tut+ik
                                                    % adb gaurko+a bezalakoak onartzeko
                                                    % gaur+a ezin da, morfotaktikak ez duelako uzten
				edo [X1/ezaug/kas ez [gen],
				     eta [X1/ezaug/kas badago [gen],
					  X2/oina/twol ez     ["gandik", "gan", "gana", "gatik", "ganantz", "ganaino"]
					 ]
				    ] % en+gatik/gana/... ez tratatzeko hemen (r_gen_atzizki-k egingo du)
			       ],
                           eta [X1/ezaug/kat badago [adl, adt],
				X2/oina/twol ez     ["gandik", "gan", "gana", "gatik", "ganantz", "ganaino"],
				         % dutenen+gatik ez egiteko, hori r_gen_atzizki-k egiten du
                                edo [X1/ezaug/kas badago [gen, gel],
				     % dakienaren+a. dakite+n+ko + 0, dakite+n+ko + a
                                     X1/ezaug/erl badago [erlt]
                                     % adizkiak elipsirik ez dagoenean: dakien+a 
                                    ]
                               ],
                           eta [X1/ezaug/kat      <=>    adi,
				X1/ezaug/adm      badago [adize],
                                X1/ezaug/kas_plus badago ["abl_gel", "abu_gel", "soz_gel"]
                               ]
                                 % ekartzetiko/ekartzerainoko/ekartzearekiko(adize) + 0/abs/soz/...
                          ]),
                 m(2, edo [X1/ezaug/azp              ez     [izb, lib], 
                      % det-dzh guztiak erregela honekin tratatuko dira
                           X1/oina/sarrera/'Sarrera' <=>    "bat",
				% beraz, hau soberan dago det-dzh delako, eta aurrekoa
			        % beteko duelako
                           eta [X1/ezaug/azp         badago [izb, lib],
                                X1/ezaug/kas         badago [gen, gel]     % izan daiteke plu+ ("gabonenek") edo plu- ("peiorenek")
                                % *keparen+ek, hemen ez dago izen berezien komunztadura
                               ]
                          ]), 
                 m(3, X2/ezaug/kat            <=>    knmdek),

% 2006-II-22 Koldok kendu du murrizpen hau. ala_gel/soz_gel beste kasuak bezala konbina daitezke. Diferentzia bakarra:
%                                          * ala_gel/soz_gel + 0-abs-mg baldin bada, orduan funtzio sintaktikoa @ADLG da
%                                          * ala_gel/soz_gel + kasua(edozein) baldin bada, orduan funtzio sintaktikoak bigarrenarenak dira
%                 m(3, edo[X1/ezaug/kas_plus       ez  ["ala_gel", "soz_gel"],
%			  "@ADLG"                 ez  X1/ezaug/fsl           % ala_gel edo soz_gel baldin bada, orduan IZLG izan behar du!
%			 ]),
				                     % ra+ko (@ADLG) atzizkiak ezin du beste atzizkirik jaso!
                                                     % Bestela ra+ko+0 egoerak 2 interpretazio sortzen ditu:
					             % ((etxe+ra)+ko)+0 eta (etxe+(ra+ko))+0
					             % Bigarren hau ez da onartuko "rako" atzizkia best gauza baterako sortu delako!
					             % desberdinak dira "rako" (r_ra_ko erregelatik sortua) eta "ra_ko" (metaketaren bidez sortua)


		 m(3, edo[X1/ezaug/kas ez [gen],
			  X2/ezaug/kas ez [pro]  % ren(gen)+tzat(pro) ez dugu onartuko, zentzurik ez duelako!!! 2005-VII-22
			 ]),
					       % gel kasua berezia da, gehienetan ez duelako mugatasuna-numeroa.
					       % Adibidez: mendi+ arentzat(m-s) + ko, BAINA: mendi + etako(m-s-gel)
		                               % Horregatik aurreko morfema batetik hartuko du, berak ez baldin badauka
		 m(3, edo[eta[X2/ezaug/kas     badago [gel],
			      X2/ezaug/mug     ez     [m, mg],
			      X0/ezaug/mug     <=>    X1/ezaug/mug,  
			      X0/ezaug/num     <=>    X1/ezaug/num
			     ],
                                               % izenordeak, adib.: 
                                               %                    gu(num:p)+0(mug:mg)
                                               %                    ni(num:s)+0(mug:mg)
                                               %  numeroa goratuko da, eta mugatua jarriko da 
                          eta[X1/ezaug/kat     <=>    ior,
                              X1/ezaug/num     badago [p, s],
                              X0/ezaug/mug     <=>    m,
                              X0/ezaug/num     <=>    X1/ezaug/num
                             ],
                                               % determinatzaile erakusleak, adib.: 
                                               %                    hau(nmg:p)+ekin
                                               %                    hon(nmg:s)+ekin
                                               %  numeroa goratuko da, eta mugatua jarriko da. nmg ez da goratuko
                          eta[X1/ezaug/kat     <=>    det,
                              X1/ezaug/nmg     badago [p, s],
                              X1/ezaug/azp     badago [erkarr],
                              X0/ezaug/mug     <=>    m,
                              X0/ezaug/num     <=>    X1/ezaug/nmg
                             ],
                                               % Beste determinatzaileak, adib.: 
                                               %                    bi(nmg:p)+ri(mug:mg)         -> nmg:p  mug:mg 
                                               %                    zein(nmg:mg)+0(mug:mg)       -> nmg:mg mug:mg 
                                               %                    zein(nmg:mg)+a(mug:m num:s)  -> nmg:mg mug:m num:s 
                                               %                    zein(nmg:mg)+ek(mug:m num:p) -> nmg:mg mug:m num:s 
                                               %  dena goratuko da
                          eta[X1/ezaug/kat     <=>    det,
                              X1/ezaug/nmg     badago [p, s, mg],
                              X1/ezaug/azp     ez     [erkarr],
                              X0/ezaug/nmg     <=>    X1/ezaug/nmg,
                              X0/ezaug/num     <=>    X2/ezaug/num,
                              X0/ezaug/mug     <=>    X2/ezaug/mug
                             ],
			  eta[X0/ezaug/mug     <=>    X2/ezaug/mug,  % Bestela, bigarren osagaiak du numero+mugatasuna
			      X0/ezaug/num     <=>    X2/ezaug/num
			     ]
			 ]),
	  
                                              % m(4, X1/ezaug/kas ez [gen, gel]), murriztapen hau "mendikoa"(elipsirik gabe) onartzeko kendu da
                 m(4,  X0/forma               <=>    X1/forma),
                 m(5,  X0/ezaug/kat           <=>    X1/ezaug/kat),
                 m(6,  X0/ezaug/azp           <=>    X1/ezaug/azp),
                 m(7,  X0/oina                <=>    X1/oina),
                 m(9,  X0/ezaug/oin           <=>    X1/ezaug/oin),
                 m(10, X0/ezaug/atzl          <=>    X1/ezaug/atzl),
                 m(11, X0/ezaug/adm           <=>    X1/ezaug/adm),
                 m(11, X0/ezaug/aurl          <=>    X1/ezaug/aurl),
                 m(11, X0/ezaug/oinkatazp     <=>    X1/ezaug/oinkatazp),

					       % kas_plus: ABZ: ranz+ko, arenganantz+ko,
					       %           ABL: tik+ko, 
					       %           ABU: raino+ko, arenganaino+ko 
					       %           MOT: arengatik+ko
					       %           INS: z+ko?
					       %           INE: ?
					       %           DES: ?
                 m(11, edo[eta[X1/ezaug/kas  badago [abl, abu, abz, des, ins, mot,
						     ine, des,
                                                     ala, soz],
			       X2/ezaug/kas badago [gel],
			       X0/ezaug/kas_plus <=> $($(X1/ezaug/kas, "_"), X2/ezaug/kas)
			      ],
			   X0/ezaug/kas_plus      <=>    X2/ezaug/kas_plus % bestela goratu zegoena, zerbait balego!
			  ]),
		       
                 m(13, X0/id                  <=>    X1/id),
                 m(14, edo[
		            eta  [X1/ezaug/kat          <=>    adi,
				  X1/ezaug/adm          badago [adize],
				  X1/ezaug/kas_plus     badago ["ala_gel", "soz_gel"],
				  X2/ezaug/mug          badago [mg],
				  X2/ezaug/kas          badago [abs],
	                          X0/ezaug/fsl          <=>    ["@-JADNAG_MP_ADLG"]  % Kasu honetan (ra+ko)/(ki+ko) + 0-abs-mg ez da @OBJ, @SUBJ, @PRED
				 ],
		            eta  [X1/ezaug/kat          <=>    adi,
				  X1/ezaug/adm          badago [adize],
	                          X0/ezaug/fsl          <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl) % bestela, adize bada, hau egin
				 ],
		            eta  [X1/ezaug/kat          <=>    adl,
	                          edo [eta[X2/ezaug/kas badago [gen, gel],
				           X0/ezaug/fsl <=>    ["@+JADLAG_MP_IZLG>"]
					  ],
	                               X0/ezaug/fsl     <=>    gehitu_aurrizkia("@+JADLAG_MP_", X2/ezaug/fsl)]
				      ],
		            eta  [X1/ezaug/kat          <=>    adt,
	                          edo [eta[X2/ezaug/kas badago [gen, gel],
				           X0/ezaug/fsl <=>    ["@+JADNAG_MP_IZLG>"]
                                          ],
	                                X0/ezaug/fsl    <=>    gehitu_aurrizkia("@+JADNAG_MP_", X2/ezaug/fsl)]
				  ],
		            eta  [X1/ezaug/kas_plus     badago   ["ala_gel", "soz_gel"],  % Beste kasu bat (2006-II-22):
                                                                     % ala_gel/soz_gel + 0-abs-mg denean, orduan funtzio sintaktikoa @ADLG da
	                          X2/ezaug/kas <=> abs,
	                          X2/ezaug/mug <=> mg,
				  X0/ezaug/fsl <=>    ["@ADLG"]
                                 ],
			    X0/ezaug/fsl                <=>    X2/ezaug/fsl  % azken aukera: beste kasuak ez badira betetzen, orduan kopiatu dagoena
                          ]),
                 m(14, X0/morf_lista                    <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(14, X0/lema_osatua                   <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol              <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua                <=>    X1/aldaera_osatua ),
                 m(14, X0/erat                          <=>    X1/erat),
                 m(15, X0/twolt                         <=>    $($(X1/twolt, "+"), X2/twolt))]).


% adi-part + kasu-marka
% Hauek funtzio sintaktiko konposatuak sortzen dituzte
% Adibidez: egin + -arekin (@-JADNAG_MP_ADLG), egin + -ez
% makurtu+ago + 0
rule(r_adipart_gehi_knmdek, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat           <=>    adi),    % adi-part adjektiboa bezalakoa izateko
		 m(2,  X1/ezaug/adm           badago [part]),
		 m(3,  X2/ezaug/kas           ez     [mot]),  % egin+agatik ez hartzeko
                 m(4,  X2/ezaug/kat           <=>    knmdek),
	         m(5,  edo [X1/ezaug/kas      ez     [gen],
			    eta [X1/ezaug/kas badago [gen],
				 X2/oina/twol ez     ["gandik", "gan", "gana", "gatik", "ganantz", "ganaino"]
				]
			   ]),        % en+gatik/gana/... ez tratatzeko hemen (r_gen_atzizki-k egingo du)
                 m(6,  X0/forma            <=>    X1/forma),
		 m(7,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(8,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(8,  X0/ezaug/adm        <=>    X1/ezaug/adm),
                 m(9,  X0/oina             <=>    X1/oina),
                 m(5,  X0/ezaug/mug        <=>    X2/ezaug/mug),   
                 m(5,  X0/ezaug/num        <=>    X2/ezaug/num),   
                 m(11, X0/ezaug/oin        <=>    X1/ezaug/oin),
                 m(12, X0/ezaug/atzl       <=>    X1/ezaug/atzl),
                 m(13, X0/ezaug/aurl       <=>    X1/ezaug/aurl),
                 m(11, X0/ezaug/oinkatazp  <=>    X1/ezaug/oinkatazp),
                 m(14, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
		 m(16, edo[eta[ X1/oina/sarrera/'Sarrera' <=> "izan",
                                X1/ezaug/kas        ez [gen, gel],    % "izan" hutsa izan behar du, ez dute balio "izandako" edo antzekoak  
                                X2/ezaug/kas              <=> abs,     % "izan" kasu berezia da: "kepa IZAN da" "kepa ibili IZAN da" 2005-VI-30
                                X2/ezaug/mug              <=> mg,
                                X0/ezaug/kas              <=> abs, 
                                X0/ezaug/mug              <=> mg,
                                X0/ezaug/fsl              <=> ["@-JADNAG_MP_OBJ", "@-JADNAG_MP_SUBJ", "@-JADNAG_MP_PRED", 
                                                              "@-JADLAG_MP_OBJ", "@-JADLAG_MP_SUBJ", "@-JADLAG_MP_PRED"] 
                              ],
                           X0/ezaug/fsl                  <=> gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)
                          ]),
                 m(17, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).





% gehitu_morf_lista(L1, L2)
% morfemen lista osatzen du, ondoko baldintzekin:
%   * L1 eta L2 morfemak badira, 
%           orduan bien morfemen listen kateaketa. (adib.: aren + tzat)
%           bestela L1 lema bada L2 emango du (adib.: mendi + a)
% Orokorrean: morfemen lista osatzeko funtzioa da.
% Kasu desberdinak egon daitezke, zeren lista hori elementu bakoitzak osatuta
%  edo osatu gabe izan dezake, adibidez:
%              mendi + a, 
%              eman + 0, 
%              apur + tu
%              (mendi+txo) + a
%              (apur+tu) + 0
%              (aren+tzat) + ko
%              eta + ko
%              ba + dago
%              (eman+0) + da





% adib.: guraize + ak, *guraize + a
rule(r_lehen_knmdek_arrunta_plurala_plus, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        badago [ize]),
                 m(2,  X1/ezaug/azp        ez     [izb, lib]),
                 m(3,  X2/ezaug/kat        <=>    knmdek),
                 m(4,  X2/ezaug/num        badago [p]),
                 m(5,  X1/ezaug/plu        badago ["+"]), % <=> jarriz gero, gizon+ak egingo luke
                 m(6,  X0/forma            <=>    X1/forma),
                 m(7,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(8,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(5,  X0/ezaug/mug        <=>    X2/ezaug/mug),   
                 m(5,  X0/ezaug/num        <=>    X2/ezaug/num),   
                 m(9,  X0/oina             <=>    X1/oina),
                 m(10, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
                 m(12, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).



% adib.: (Estatu Batu) + ak, Gabon + ak (mugatasun lexikala)
rule(r_lehen_knmdek_berezia_plurala_plus, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    ize),
                 m(2,  X1/ezaug/azp        badago [izb, lib]),
                 m(3,  X2/ezaug/kat        <=>    knmdek),
                 m(4,  X1/ezaug/kas        ez     [gen, gel]),
                 m(5,  X0/forma            <=>    X1/forma),
                 m(6,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(7,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(5,  X0/ezaug/mug        <=>    X2/ezaug/mug),   
                 m(5,  X0/ezaug/num        <=>    X2/ezaug/num),  
                 m(8,  X2/ezaug/num        <=>    p),
                 m(9,  X0/oina             <=>    X1/oina),
                 m(10, X1/ezaug/plu        badago ["+"]),
                 m(11, X2/ezaug/mug        <=>    m),     % honek "peio+0(mug mg)" ere baztertuko du
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
                 m(14, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).



% adib.: *kepa + ri, *peio + 0(mg), *lekeitio(plu -) + 0
rule(r_lehen_knmdek_berezia_plurala_minus, X0 ---> [X1, X2]@[
                 m(1, X1/ezaug/kat         <=>    ize),
                 m(2, X1/ezaug/azp         badago [izb, lib]),
                 m(3, X2/ezaug/kat         <=>    knmdek),
                 m(4, X1/ezaug/kas         ez     [gen, gel]),
				% hauek r_lehen_knmdek erregelaren bidez tratatuko dira
				% adib.: *keparen(s)+ek(p)
                 m(5,  X0/forma            <=>    X1/forma),
                 m(6,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(7,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(8,  X0/ezaug/mug        <=>    m), % izen bereziek mugatasun lexikala dute
                 m(9,  X0/ezaug/num        <=>    s),
                 m(10, X0/oina             <=>    X1/oina),
                 m(11, X1/ezaug/plu        ez     ["+"]),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
                 m(14, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).




% Erregela honek genitibo ondoren elipsirik ez dagoen kasuetan kasu-marka berria sortuko 
% du bi morfematik abiatuta.
% knmdek -> gen + dek (gan/gana/gandik/gatik/ganantz/ganaino)
% ad.: aren + gana (gizonarengana)
rule(r_gen_atzizki, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat      <=>    dek),
                 m(2,  X2/ezaug/kat      <=>    dek),
                 m(3,  X1/ezaug/kas      badago [gen]),
                 m(4,  X2/ezaug/kas      badago [abl, ine, ala,  mot,   abu,    abz]),
                 m(5,  X2/oina/twol      badago ["gan", "gana", "gandik", "gatik", "ganantz", "ganaino"]),
                 m(6,  X0/forma          <=>    X1/forma),
                 m(7,  X0/ezaug/kat      <=>    knmdek),
                 m(5,  X0/ezaug/mug      <=>    X1/ezaug/mug),
                 m(5,  X0/ezaug/num      <=>    X1/ezaug/num),
                 m(8,  X0/morf_lista     <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
	         % m(7,  X0/ezaug/kas_plus <=>    $($(X1/ezaug/kas, "_"), X2/ezaug/kas)),
                 m(15, X0/twolt          <=>    $($(X1/twolt, "+"), X2/twolt))]).




% knmdek -> dek (abs, erg, dat, gen, ins, par, pro, mot(diru+gatik))
% deklinabide-atzizki sinpleak, kasua eta mugatasuna/ezaug/numeroa ere definituta dituenak
% ad.: a, ek, ari (etxea, etxeek, etxeari testuinguruetan)
rule(r_kasu_atzizkia, X0 ---> [X1]@[
                 m(1,  X1/ezaug/kat  <=>    dek),
                 m(2,  X1/ezaug/kas  badago [abs, erg, dat, gen, ins, par,
                                             ine, % inesiboa normalean ez da erregela honekin
				                  % egiten: mendi+(0+an).
						  % salbuespena: bat(det)+en
                                             gel, abl, ala, soz, abu, des, abz,
				                  % beste salbuespen bat:
						  %  bere(det)+ko/tik/ra/kin/raino/tzat/rantz
						 pro, bnk, desk, mot]), 
                 m(3,  X0/forma      <=>    X1/forma),
                 m(4,  X0/ezaug/kat  <=>    knmdek),
                 m(5,  X0/twolt      <=>    X1/twolt),
                 m(6,  X0/ezaug/mug  <=>    X1/ezaug/mug),
                 m(7,  X0/ezaug/num  <=>    X1/ezaug/num),
                 m(8,  X0/ezaug/kas  <=>    X1/ezaug/kas),
                 m(9,  X0/ezaug/fsl  <=>    X1/ezaug/fsl ),
                 m(10, X0/oina       <=>    X1/oina ),
                 m(11, X0/morf_lista <=>    X1/morf_lista )]).


% Erregela hau kasua eta mugatasuna/ezaug/numeroa banatuta doazenean aplikatuko da. 
% Ezaugarriak biltzen ditu, eta knmdek kategoria sortzen du.
% knmdek --> 0/eta/ph + ko/ra/tik/raino/rantz
% adib: 0+ko, 0+ra, 0+an, 0+tik, 0+raino (mendiko, mendira, menditik, mendiraino)
%       ota+n (plural hurbila)
%	eta+ko, ..., eta+raino (mendietako, mendietara, mendietatik, mendietaraino)
rule(r_mendi_eta_ra, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    dek),
                 m(2,  X2/ezaug/kat              <=>    dek),
                 m(3,  X1/oina/sarrera/'Sarrera' badago ["0", "eta", "ta", "ota"]),
                 m(4,  X2/ezaug/kas              badago [gel, ine, abl, ala, abu, abz]),
                 m(5,  X2/oina/twol              ez     ["gandik", "gan", "gana",
				                         "gatik", "ganantz", "ganaino"]),
				                         % 0 + gatik/gandik/... ez egiteko
				                         %        (r_agana_lakoak erregelak egiten ditu)
                 m(6,  X0/forma                 <=>    X1/forma),
                 m(7,  X0/ezaug/kat             <=>    knmdek),
                 m(5,  X0/ezaug/mug             <=>    X1/ezaug/mug), 
                 m(5,  X0/ezaug/num             <=>    X1/ezaug/num), 
                 m(8,  X0/oina                  <=>    X2/oina), % bat hartzearren. Gaizki???
                 m(9,  X0/morf_lista            <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                 <=>    $($(X1/twolt, "+"), X2/twolt))]).



% dek -> dek-sing(a) + gan/gana/gandik/gatik/ganantz/ganaino
% ad.: a + gana (gizonagana testuinguruan)
% dek -> dek-mg(0)   + gan/gana/gandik/gatik/ganantz/ganaino (izenordeekin: nigatik, ...)
% ad.: 0 + gana (nigana testuinguruan)
rule(r_agana_lakoak, X0 ---> [X1, X2]@[
                 m(1,  X1/oina/sarrera/'Sarrera' badago ["a", "0"]),
                 m(2,  X1/ezaug/kat              <=>    dek),
                 m(3,  X2/ezaug/kat              <=>    dek),

		 m(4,  X2/oina/twol              badago ["gandik", "gan", "gana",
				                         "gatik", "ganantz", "ganaino"]),   
                  % m(4,  X2/ezaug/kas     badago [abl, ine, ala, mot, abu, abz]),
		  % hau jarriz gero, 0+ean modukoak ere sartzen ziren, eta horiek beste
		  % erregela batekin doaz
		  % Agian erregela hau eta aurrekoa bildu daitezke!!!
                 m(5,  X0/ezaug/kat              <=>    knmdek),
                 m(5,  X0/ezaug/mug              <=>    X1/ezaug/mug),
                 m(5,  X0/ezaug/num              <=>    X1/ezaug/num),
                 m(6,  X0/oina                   <=>    X2/oina),
		 m(7,  X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))]).


/*
% 2005-VII-21 Erregela berria: ra + ko sortuko da, ADLG funtzioarekin (adib.: etxerako)
% Baina hori egiteko kontuz ibili behar gara, ra+ko eta ra+ko+0, biak egiten direlako.
% Soluzioa:
% Adibideak: ra + ko (etxerako), rat + ko, gana + ko (amaganako), etxe + arekin + ko, ete + aren + gana + ko
rule(r_ra_ko, X0 ---> [X1, X2]@[
                 m(2,  X1/ezaug/kat            <=>        knmdek),
                 m(3,  X2/ezaug/kat            <=>        knmdek),
                 m(2,  X1/ezaug/mug            definitua), % aren+gana, a+gana, 0+ra izateko, baina ez "gana" (ezin da gertatu "gana" hutsa?)
                 m(2,  X1/ezaug/kas            badago     [ala, soz]),
                 m(3,  X2/ezaug/kas            <=>        gel),
                 m(5,  X0/ezaug/kat            <=>        knmdek),
                 m(5,  X0/ezaug/mug            <=>        X1/ezaug/mug),
                 m(5,  X0/ezaug/num            <=>        X1/ezaug/num),
                 m(5,  X0/ezaug/kas            <=>        X2/ezaug/kas),
                 m(6,  X0/ezaug/kas_plus       <=>        $($(X1/ezaug/kas, "_"), X2/ezaug/kas)),
                 m(6,  X0/oina                 <=>        X2/oina),
                 m(6,  X0/ezaug/fsl            <=>        ["@ADLG"]),
                 m(7,  X0/morf_lista           <=>        gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                <=>        $($(X1/twolt, "+"), X2/twolt))]).
*/




% knmdek -> au/or + knmdek
% adibideak: on+ekin ("honekin guztion+ekin" testuinguruan), 
%            or+engana ("horrengana guztior+engana" testuinguruan), 
rule(r_honekin_guztionekin, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    dek),
                 m(2,  X2/ezaug/kat              <=>    knmdek),
                 m(3,  X1/oina/sarrera/'Sarrera' badago ["au", "ori"]),
                 m(4,  X0/forma                  <=>    X1/forma),
                 m(5,  X0/ezaug/kat              <=>    knmdek),
                 m(5,  X0/ezaug/mug              <=>    X1/ezaug/mug), 
                 m(5,  X0/ezaug/num              <=>    X1/ezaug/num),
                 m(6,  X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))]).


% "Cortazar-ek" bezalakoak analizatzeko, erregela berria sartuko dut
% dek -> MARRA dek
rule(r_marra_dek, X0 ---> [X1, X2]@[
     m(1,  X1/ezaug/kat  <=> mar),
     m(2,  X2/ezaug/kat  <=> dek),
     m(3,  X0/ezaug/kat  <=> dek),
     m(5,  X0/ezaug/mug  <=> X2/ezaug/mug),
     m(5,  X0/ezaug/num  <=> X2/ezaug/num),
     m(4,  X0/forma      <=> X1/forma),
     m(5,  X0/oina       <=> X2/oina),
     m(6,  X0/morf_lista <=> gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
     m(12, X0/id         <=> X1/id), 
     m(15, X0/twolt      <=> $($(X1/twolt, "+"), X2/twolt))]).





% *********************** Gradua ********************************************************
% Erregela honek adjektiboei graduatzailea (-en edo -ago) gehitzea onartuko du. Kategoria 
% eta azpikategoria mantenduko dira, eta grm ezaugarrian markatuko da graduatzailea 
% agertu dela

% adj/adi-part/adb-> adj/adi-part/adb + grad 
% adib.: handi + ago, handi + en
% 	 makurtu + ago
% 	 maiz + ago
%        honekin + txe
%        asto/gizon + ago
%        norenera+ago
% baina ez *gaur+ago
% hemen ez dut jarri adi-mod, nahiz eta batzuetan adberbioaren papera egin
%        "emandagoa" ez delako onartzen
rule(r_graduatzailea, X0 ---> [X1, X2]@[
                 m(1,  edo [X1/ezaug/kat      badago [adj, adb, det, ize, ior, eli],
                            eta [X1/ezaug/kat <=>    adi,
                                 X1/ezaug/adm badago [part]
				         % adi-part adjektiboa bezalakoa izateko
                                ],
                            eta [X1/ezaug/kat <=>    adi,
                                 X1/ezaug/asp badago [ezbu]
				         % zabaltzen(ezbu)+ago
                                ]
                           ]),
                 m(2,  X0/forma            <=> X1/forma),
                 m(3,  X2/ezaug/kat        <=> gra),
                 m(5,  X0/ezaug/mug        <=> X1/ezaug/mug),
                 m(5,  X0/ezaug/num        <=> X1/ezaug/num),
                 m(5,  X0/ezaug/adm        <=> X1/ezaug/adm),
                 m(4,  X0/ezaug            <=> X1/ezaug),
                 m(5,  X0/oina             <=> X1/oina),
                 m(6,  X0/id               <=> X1/id),
                 m(14, X0/lema_osatua      <=> X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=> X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=> X1/aldaera_osatua ),
                 m(14, X0/erat             <=> X1/erat),
                 m(8,  X0/morf_lista       <=> gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=> $($(X1/twolt, "+"), X2/twolt))]).
% Adibidez: handi + ago

% handi             +          ago                         =   handiago
% gune twol handi              gune twol ago                   kat adj
%                                                              grad ago
% sar handi                    sar ago                         mug - (indefinitua)
% kat adj                      kat gra                         azp izo
% azp izo                      forma handiago                  sar handiago
% forma handiago	





% *********************** ELIPSIA ********************************************************
% Informazioa egituratuta egongo da:
%
% gizonaren + ELI +   aren       +  ELI  + a          = gizonarenarena
% kat ize             kat knmdek           kat knmdek   kat izeeli
% kas gen             num s                num s        kas abs
% mug m               mug m	           mug m        mug m
% num s               kas gen              kas abs      num s
% biz -               sar ren	                        osagai_lista  elem kat ize
% zenba -	                                                           kas gen
% neur -	                                                           mug m
% azp arr	                                                           num s
% grad -  	                                                           biz -
% sar gizonaren	                                                           zenba -
% 	                                                                   neur -
%                                                                          azp arr
%                                                                          grad -
%                                                                          sar gizonaren
%                                                                    elem  kat eli
%                                                                          kas gen
%                                                                          mug m
%                                                                          num s
%                                                                          azp arr
%                                                                          sar 0aren
%                                                                    elem  kat eli
%                                                                          kas abs
%                                                                          mug m
%                                                                          num s
%                                                                          sar 0a


% Erregela honek adizkiek eta izenkiek ekartzen duten elipsia tratatzen du.
% Adizkia + elipsia hartzen du. Honen ondoren elipsi gehiago balego, izen eliptikoa
% lortu denez, r_osagai_eliptikoak erregelarekin lotuko dira
% Agian beste erregela bakarrarekin 
rule(r_osagai_eliptikoak, X0 ---> [X1, X2]@[
                 m(1,  edo [eta[X1/ezaug/erl          badago [erlt],       % adizkiak: duen+a
				X1/ezaug/kat          ez     [erl]],       % baina ez -n atzizki hutsa!
                            eta[X1/ezaug/kas          badago [gen, gel],   % amaren+a
                                X1/ezaug/kat          ez     [dek, knmdek] % baina ez -ko atzizki hutsa!
                               ]
                           ]),
                 m(2,  edo[X2/ezaug/kat               <=>    eli,
			   eta[X2/ezaug/kat           <=>    ize,
			       X2/ezaug/oin/'Sarrera' badago ["0"]]]),
					    %  bigarren kasua: 0+txo (adib: "dagoen + 0(eli)+txo(erakat ize)", 0+txo kat:ize, baina ELI da,
					    %  eratorria izatea eskatuko da, bestela ELI
					    %  hutsarekin (0) lotu litekeelako)
                 m(3,  edo[X2/ezaug/mug               badago [mg, m],
				% hau osagai eliptiko hori deklinatua izateko, bestela
			        % gehiegi sortzen duelako
			   eta[X2/ezaug/kat           <=>    ize,
			       X2/ezaug/oin/'Sarrera' badago ["0"]]]), % lehengo kasua: 0+txo
                 m(4,  X0/forma                <=> X1/forma),
                 m(5,  X0/ezaug/kat            <=> $($(X1/ezaug/kat, "_"), "izeeli")),
                 m(5,  X0/ezaug/mug            <=> X2/ezaug/mug),
                 m(5,  X0/ezaug/num            <=> X2/ezaug/num),
                 m(6,  X0/oina                 <=> X1/oina),
		     % kasu honetan bi oin daude, dena dela lehenengoa hartuko dut
                 m(7,  X0/ezaug/beste          <=> X1/ezaug/beste),
                 m(14, X0/lema_osatua          <=> X1/lema_osatua ), % ???
                 m(14, X0/lema_osatua_twol     <=> X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua       <=> X1/aldaera_osatua ),
                 m(14, X0/erat                 <=> X1/erat),
                 m(12, X0/id                   <=> X1/id),
                 m(15, X0/twolt                <=> $($(X1/twolt, "+"), X2/twolt)),
                 m(9,  eta([Osagai1/oina       <=> X1/oina,
			    Osagai1/ezaug      <=> X1/ezaug,
			    Osagai1/morf_lista <=> X1/morf_lista,
			    Osagai2/oina       <=> X2/oina,
			    Osagai2/ezaug      <=> X2/ezaug,
			    Osagai2/morf_lista <=> X2/morf_lista,
			    X0/osagai_lista    <=> gehitu_osagai_listak(X1/osagai_lista, Osagai1, Osagai2)]))
			       ]).
                                      % Osagai1-ek osagairik badu ("mendiko+aren"), orduan gehitu,
                                      % ez badu ("mendiko", hau da, lehen osagaia da), berarekin hasieratu lista



% Adizki jokatugabeenak
% Oinarrizkoa: aditzoina, partizipioa, ...


% Erregela honek aditz mota lortzen du. Aditz mota adm ezaugarrian uzten du atzizkiaren 
% adm ezugarritik hartuta.

% aditza--> aditza + amm (partizipioa/adoin)
% adib.: 	etor+i, makur+tu, eman+0 	(partizipioa)
% 		etor+0 				(aditz-oina)

% adi-gero --> aditza-partizipioa + etorkizuneko marka 
%  adib.: eman+GO
% adi-burutua --> aditza + bukatuaren marka 
% adib:   (etor+i) + 0, (makur+tu) + 0, (eman+0-part) + 0-buru

% adi-ezbu --> aditza + ez bukatuaren marka 
% adib:  eman+(0+ten), etor+(0+tzen), itxi+ten
%        etor+i, etor+0, etor+tzeko
rule(r_adimota, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat           <=>    adi),
                 m(2,  edo([eta[X2/ezaug/kat  <=>    amm,
                                X2/ezaug/adm  badago [part, adoin]],
			    eta[X2/ezaug/kat  <=>    asp,
				X2/ezaug/asp  badago [gero, buru]],
			    eta[% X1/ezaug/adm  badago [adoin], % ekar+0+tzen, baina itxi+ten! Biak onartu behar dira!
				X2/ezaug/kat  <=>    asp,
				X2/ezaug/asp  badago [ezbu]]])),
                 m(3,  X0/forma               <=>    X1/forma),
                 m(4,  X0/ezaug/kat           <=>    adi),
                 m(5,  X0/ezaug/azp           <=>    X1/ezaug/azp),
                 m(5,  X0/ezaug/adm           <=>    X2/ezaug/adm),
                 m(6,  X0/oina                <=>    X1/oina),
                 m(6,  X0/ezaug/oin           <=>    X1/ezaug/oin),
                 m(7,  X0/ezaug/aurl          <=>    X1/ezaug/aurl),
                 m(12, X0/id                  <=>    X1/id),
                 m(14, X0/lema_osatua         <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol    <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua      <=>    X1/aldaera_osatua ),
                 m(14, X0/erat                <=>    X1/erat),
                 m(8,  X0/morf_lista          <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt               <=>    $($(X1/twolt, "+"), X2/twolt))]).
      



% Partizipioaren gainekoak (-ta, )

% --> aditza(partizipio) + erl (ta/da)
% adib:  eman+da(mod), joan + keran(denb)
% adizki jokatugabeen adizkiak
rule(r_adi_ta, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    adi),
                 m(2,  X1/ezaug/adm        badago [part]),
                 m(3,  X2/ezaug/kat        <=>    erl),
                             % m(4,  X2/ezaug/azp  <=>    men), % orain desagertu da 4.4.3n
                 m(5,  X2/ezaug/erl        badago [mod, denb]), 
                 m(6,  X0/forma            <=>    X1/forma),
                 m(7,  X0/ezaug/kat        <=>    adi),
                 m(8,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(8,  X0/ezaug/adm        <=>    X1/ezaug/adm),
                 m(9,  X0/oina             <=>    X1/oina),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
                 m(10, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
		 m(11, X0/ezaug/fsl        <=>    ["@-JADNAG_MP_ADLG"]),
                 m(11, X0/ezaug/erl        <=>    X2/ezaug/erl), 
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).



/* EZ DU BALIO (2011-III-25). EZ DA APLIKATZEN, ADIBIDEZ "izaki"
% --> aditza + erl (ki)
% adib:  izan + ki
% adizki jokatugabeen adizkiak
% Hau berezia "izaki"-k aditz nagusia zein laguntzailearen papera egin dezakeelako ("han bizi izaki" Koldok asmatua! "bizi izan da"-ren parekoa nahi nuen topatu)
rule(r_izan_ki, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    adi),
                 m(1,  X1/lema_osatua      <=>    "izaN"),
                 m(2,  X1/ezaug/adm        ez     [part, adoin]),
                 m(3,  X2/ezaug/kat        <=>    erl),
                 m(3,  X2/oina/twol        <=>    "ki"),
                 m(5,  X2/ezaug/erl        badago [mod]), 
                 m(6,  X0/forma            <=>    X1/forma),
                 m(7,  X0/ezaug/kat        <=>    adi),
                 m(8,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(8,  X0/ezaug/adm        <=>    X1/ezaug/adm),
                 m(9,  X0/oina             <=>    X1/oina),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua),
                 m(14, X0/erat             <=>    X1/erat),
                 m(10, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(11, X0/ezaug/erl        <=>    X2/ezaug/erl), 
		 m(11, X0/ezaug/fsl        <=>    ["@-JADNAG_MP_ADLG", "@-JADLAG_MP_ADLG"]),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).
*/




% Partizipioaren gainekoak (-agatik, ...)

% aditza(partizipio) + dek-mot
% aditza(adize)      + dek-mot
% adib: ikusi+agatik, ikuste+agatik
% adizki jokatugabeen adizkiak
rule(r_adi_gatik, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    adi),
                 m(2,  X1/ezaug/adm        badago [part, adize]),
                 m(3,  X1/ezaug/kas        ez     [gen]), % emandakoaren+gatik ez egiteko
					                % emandako+ (aren+gatik) egingo da
                 m(4,  X2/ezaug/kat        <=>    knmdek),
                 m(5,  X2/ezaug/kas        badago [mot]), 
                 m(6,  X0/forma            <=>    X1/forma),
                 m(7,  X0/ezaug/kat        <=>    adi),
                 m(8,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(8,  X0/ezaug/adm        <=>    X1/ezaug/adm),
                 m(5,  X0/ezaug/mug        <=>    X2/ezaug/mug),
                 m(5,  X0/ezaug/num        <=>    X2/ezaug/num),
                 m(9,  X0/ezaug/erl        <=>    kont),
                 m(10, X0/oina             <=>    X1/oina),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
		 m(11, X0/ezaug/fsl        <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(12, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).




% Erlazio-morfemak

% Adizki jokatuenak
% Erlatiboa eta bere eratorriak (-(e)nean, -(e)neko, ...), konpletiboa eta bere eratorriak (-
% (e)larik, -(e)lako, ...)

% adl/adt --> adl/adt + (erlt, konpl, zhg)  
% adib:  de+n(erlatibo), da+la(konpl), dakite+la(konpl), dakite+n (zhg)
%    dakite+la(mod/denb), dakite+nean (denb), dakite+neko (denb), dakite+larik (mod/denb)
rule(r_aditz_jok_loturak, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        badago [adl, adt]),
                 m(2,  X2/ezaug/kat        <=>    erl),
                 m(2,  X2/oina/ezaug/erl   ez     [kaus, denb, helb, mod, mos, 'mod/denb']), % konpl, erlt edo zhg izan behar da
                              % kaus/denb/mod/helb/mos? (de+lako) salbuespena da, @+JADNAG_MP_ADLG sortu behar delako 2005-VI-30
                              % m(3,  X2/ezaug/azp  <=>    men), % 4.4.3n desagertu da
                 m(4,  X0/forma            <=>    X1/forma),
                 m(5,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(6,  X0/oina             <=>    X1/oina),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
                 m(11, X0/ezaug/erlatz     <=>    X2/oina/sarrera/'Sarrera'), % 2005-I-20 Bereizteko zein atziki den! 
                 m(7,  X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                   % 2005-VI-29: bereizteko ea laguntzailea ala nagusia den ("desanbiguazioaren" antzekoa):
                 m(15, edo[eta[X2/oina/ezaug/erl    badago [konpl],
                               edo[eta[X1/ezaug/kat <=>    adl,
                                       X0/ezaug/fsl <=>    ["@+JADLAG_MP_SUBJ", "@+JADLAG_MP_OBJ", "@+JADLAG_MP_PRED"]
                                      ],
                                   eta[X1/ezaug/kat <=>    adt,
                                       X0/ezaug/fsl <=>    ["@+JADNAG_MP_SUBJ", "@+JADNAG_MP_OBJ", "@+JADNAG_MP_PRED"]
                                      ]
                                  ]
                              ],
                           eta[X2/oina/ezaug/erl    badago [erlt],
                               edo[eta[X1/ezaug/kat <=>    adl,
                                       X0/ezaug/fsl <=>    ["@+JADLAG_MP_IZLG>"]
                                      ],
                                   eta[X1/ezaug/kat <=>    adt,
                                       X0/ezaug/fsl <=>    ["@+JADNAG_MP_IZLG>"]
                                      ]
                                  ]
                              ],
                           eta[X2/oina/ezaug/erl    badago [zhg],
                               edo[eta[X1/ezaug/kat <=>    adl,
                                       X0/ezaug/fsl <=>    ["@+JADLAG_MP_OBJ"]
                                      ],
                                   eta[X1/ezaug/kat <=>    adt,
                                       X0/ezaug/fsl <=>    ["@+JADNAG_MP_OBJ"]
                                      ]
                                  ]
                              ]
                          ]),
                 m(11, X0/ezaug/erl      <=>    X2/ezaug/erl), 
                 m(15, X0/twolt          <=>    $($(X1/twolt, "+"), X2/twolt))]).





% Aurrizkiak: Ba- (baldintzazkoa), ba- (adberbio) eta bait-

% adl/adt --> ba(baldintzazkoa) + adl/adt
% adib:  badago
rule(r_ba_baldintza, X0 ---> [X1, X2]@[
                 m(1,  X2/ezaug/kat              badago [adl, adt]),
                 m(2,  X1/ezaug/kat              <=>    erl),
                 m(3,  X1/ezaug/erl              <=>    bald),
                 m(4,  X1/oina/sarrera/'Sarrera' <=>    "ba"),
                 m(3,  X2/ezaug/erl              ez     [mos, zhg, erlt]), % bestela ba + zetorren+n egingo du!!
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    X2/ezaug/kat),
                 m(6,  X0/ezaug/erl              <=>    X1/ezaug/erl),
                 m(7,  X0/oina                   <=>    X2/oina),
                 m(12, X0/id                     <=>    X1/id),
                 m(14, X0/lema_osatua            <=>    X2/lema_osatua ),
                 m(14, X0/lema_osatua_twol       <=>    X2/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua         <=>    X1/aldaera_osatua ),
                 m(14, X0/erat                   <=>    X1/erat),
		 m(11, edo[eta[X2/ezaug/kat      <=>    adl,
                               X0/ezaug/fsl      <=>    ["@+JADLAG_MP_ADLG"]
                              ],
                           eta[X2/ezaug/kat      <=>    adt,
                               X0/ezaug/fsl      <=>    ["@+JADNAG_MP_ADLG"]
                              ]
			  ]),
                 m(8,  X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))]).


% ba  aurrizkia prt  kategoriakoa izango da; ez, omen, ote ,bide bezalakoa
% 	gainera egiatasunezkoa ezaugarrian + balioa izango du.
%   zalantza: nola analizatu ba omen dute ?

% adl/adt --> ba(prt) + adl/adt
% adib:  ba+dago.
rule(r_ba_prt, X0 ---> [X1, X2]@[
                 m(1,  X2/ezaug/kat              badago [adl, adt]),
                 m(2,  X2/ezaug/erl              ez     [zhg, erlt, konpl, zhg,
						         kaus, 'mod/denb', denb, helb, mos]),
                 m(3,  X1/ezaug/kat              <=>    prt),
                 m(4,  X0/forma                  <=>    X1/forma),
                 m(5,  X0/ezaug/kat              <=>    X2/ezaug/kat),
                 m(6,  X0/oina                   <=>    X2/oina),
                 m(7,  X1/oina/sarrera/'Sarrera' <=>    "ba"),
                 m(12, X0/id                     <=>    X1/id),
                 m(14, X0/lema_osatua            <=>    X2/lema_osatua ),
                 m(14, X0/lema_osatua_twol       <=>    X2/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua         <=>    X1/aldaera_osatua ),
                 m(14, X0/erat                   <=>    X1/erat),
                 m(8,  X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))]).






% baitugu --> bait + adl/adt
% adib:  baitugu
rule(r_bait, X0 ---> [X1, X2]@[
                 m(1,  X2/ezaug/kat        badago [adl, adt]),
                 m(1,  X2/ezaug/erl        ez     [mos]), % bailiran: 2 analisi ez sortzeko
                 m(2,  X1/ezaug/kat        <=>    erl),
                                 % m(3,  X1/ezaug/azp    <=>    men),  % 4.4.3n desagertuta
                 m(4,  X1/ezaug/erl        badago [kaus, mod]),
                 m(5,  X0/forma            <=>    X1/forma),
                 m(6,  X0/ezaug/kat        <=>    X2/ezaug/kat),
                 m(7,  X0/ezaug/azp        <=>    X2/ezaug/azp),
                 m(8,  X0/oina             <=>    X2/oina),
                 m(12, X0/id               <=>    X1/id),    % lehenengoak du id-a!!!
                 m(14, X0/lema_osatua      <=>    X2/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X2/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(14, X0/erat             <=>    X1/erat),
                 m(9,  X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                         % 2005-VI-29: bereizteko ea laguntzailea ala nagusia den:
                 m(15, edo[eta[X2/ezaug/kat       <=> adl,
                               X0/ezaug/fsl       <=> ["@+JADLAG_MP_ADLG"]
                              ],
                           eta[X2/ezaug/kat       <=> adt,
                               X0/ezaug/fsl       <=> ["@+JADNAG_MP_ADLG"]
                              ]
                          ]),
                 m(11, X0/ezaug/erl        <=>    X1/ezaug/erl), 
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).



% Eratorpena

% Aurrizki lexikalak

% adib.: ez+onartu(adi), ez+jakin(adi), ez-etxe(ize), ez-polit(adj)
% beti eskatuko da oinarrizko formarekin konbinatzea,
% hau da (ber+erabil)+0, (ez- + onartu)+a, (ez- + eman)+0+da, (ez- + eman)+tea,
%        (ez- + eman)+0+go
% eta ez dira onartuko: ber + (erabil+0)       ez- + (onartu+a)

rule(r_eratorpena_aurr, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat      <=>    aur),
                 m(2,  X2/ezaug/kat      badago [ize, adj, adb, adi]),
		 m(3,  X2/ezaug/mug      ez     [m, mg]),
		 m(4,  X2/ezaug/num      ez     [s, p]),
		 m(5,  X2/ezaug/kas      ez     [desk, gel]),
			      % ez egiteko ez+(nahi(IZE)+ko(desk/gel))
		 m(6,  X2/ezaug/erat_atz ez     ['+']),
			              % azken hau ez egiteko ber+(erabil+tze)
				      % Aurrizki bat egon daiteke: ez(AUR)-(ber(AUR)-egite)
		 m(7,  X2/ezaug/adm      ez     [adize, adoin, part]),
			              % azken hau ez egiteko ez+(nahiko(ADI)+0(ADOIN))
		 m(8,  X2/ezaug/elk      ez     ["IZE+IZE", "IZE+ADIZE"]),
				      % azken hau ez egiteko ez-(onarpen-egile)
		         
                             /*         eta([X2/ezaug/kat   badago [adi],
                              %              X2/ezaug/adm   ez     [part, adize, adoin],
                              %              X2/ezaug/asp   ez     [gero, buru],
                              %              X2/ezaug/erl   ez     [mod, denb, kont, konpl, helb],
			      %		     X2/ezaug/erat  ez     [plus]
			      %             ])
		              %       Aukera hau baztertu dut, zeren uste dut [gero, buru] edo [mod, denb, konpl, ...] denean beti
                              %       delako [adize, adoin, part] eta hau lehenago egiaztatzen da
		              %       2003-V-20
			     */
                 m(9,  X0/forma                  <=> X1/forma),
		 m(10, X0/ezaug/kat              <=> X2/ezaug/kat),
		   % landu diren aurrizkiek kategoria mantentzen dute
                 m(11, X0/oina                   <=> X2/oina),
		   % nola kalkulatu lema osatua? hori egiten bada, galduko da beste lema
                 m(12, X0/ezaug/azp              <=> X2/ezaug/azp),
                 m(14, X0/ezaug/oin              <=> X2/oina/sarrera),
                 m(9,  X0/ezaug/aurl             <=> gehitu_listan_hasieran(X2/ezaug/aurl, 'Gako', X1/oina/sarrera)),
                 m(10, X0/ezaug/oinkatazp/oinkat <=> X1/ezaug/oinkat), % 2005-VI-1  hau eta hurrengoa ez dira esistitzen orain!!!
                 m(10, X0/ezaug/oinkatazp/oinazp <=> X1/ezaug/oinazp), % 2005-VI-1
					  
		 m(16, X0/ezaug/erat             <=> '+'),
                 m(12, X0/id                     <=> X1/id),

                 % m(11, edo[eta[X2/lema_osatua    definitua, % definitua baldin badago, orduan gehitu
		 % 	       X0/lema_osatua    <=>     $(X1/oina/twol, $("+", X2/lema_osatua))
		 % 	      ],
			     % bestela sortu lema_osatua
		 % 	   X0/lema_osatua        <=>     $(X1/oina/twol, $("+", X2/oina/twol))
		 % 	  ]),
                 m(14, X0/lema_osatua            <=>    $(X1/lema_osatua,      $("+", X2/lema_osatua))),
                 m(14, X0/lema_osatua_twol       <=>    $(X1/lema_osatua_twol, $("+", X2/lema_osatua_twol))),
                 m(14, X0/aldaera_osatua         <=>    osatu_aldaeraren_informazioa(X1, X2) ),

                 m(14, X0/erat                   <=>    '+'),
				       % hau al da lema osatua?
		                       % Gero sorkuntza egin beharko da, eta horregatik twol goratu behar da (diakritikoekin),
		                       % ondoren lema sortzeko.
                 m(17, X0/morf_lista             <=> gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=> $($(X1/twolt, "+"), X2/twolt))]).




/* Kendu dut 2005-VI-27
% 2004-IX-28
% aur -> aur MARRA
% ez[AUR]-[MAR]egite
% marrak ez du inolako informaziorik. Beraz, aurrizkia eta marra bilduko dira eta aurrizkia izaten jarraituko du
rule(r_aur_gehi_marra, X0 ---> [X1, X2]@[
     m(1,  X1/ezaug/kat  <=> aur),
     m(2,  X2/ezaug/kat  <=> mar),
     m(3,  X0/ezaug/kat  <=> aur),
     m(4,  X0/forma      <=> X1/forma),
     m(5,  X0/oina       <=> X1/oina),
     m(6,  X0/morf_lista <=> gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
     m(7,  X0/twolt      <=> $($(X1/twolt, "+"), X2/twolt))]).

*/



% Atzizki lexikalak

% eratorri_kat -> oinarri_kat + erat_atzizkia
% ad.: lau+garren, lagun+garri, ikusgarri+tasun, iraki+te (te atzizki lexikala izanik)
%      egin+araz
% Arazoak:
%	- funtzioa_fak: aldaketa adierazteko funtzioa, oraindik aztergai dago

% kat_apreziatibo-> kat + apreziatibo_atzizkia
% ad.: etxe+txo, zuri+txo, apurtu+txo, dagoen+txo, berandu+txo

% Problema bat: dagoentxo:
%             (dago+en)osag1 + (Eli+txo+0-abs-mg)osag2
%                   elipsiaren erregelak osagaiek kasu-marka izatea eskatzen du
%                   baina kasu honetan
%             (dago+en)osag1 + (Eli+txo)
%                   ez da hori gertatzen, eta analizatzaileak ez du hau onartzen
%                   (onartu beharko luke?)
% * adm ez da goratuko, adibidez: eduki(adm:part) + tasun = ize
%   izenak ez du adm ezaugarria izango
rule(r_eratorpena, X0 ---> [X1, X2]@[
				% m(1,  X2/lema/sarrera         ez  [txo, ño, tzar]),
				% hau kenduta atzizki arruntak eta apreziatiboa
				% berdin tratatuko dira
                 m(1,  X2/ezaug/kat              <=>     atz),
                 m(2,  X1/ezaug/kat              badago [ize, adj, adb, adi, det, eli, adl]),
				     
		 m(8,  X1/ezaug/elk      ez     ["IZE+IZE", "IZE+ADIZE"]),
			 % azken hau ez egiteko (onarpen-egile)+txo, hau da beti egingo da lehenengo eratorpena eta gero elkarketa
                 m(2,  X0/forma                  <=>     X1/forma),
                 m(3,  X0/ezaug/kat              <=>     X2/ezaug/erakat), % 2005-V-24
                 m(4,  X0/ezaug/azp              <=>     X2/ezaug/eraazp), % 2005-V-24
                 m(5,  X0/oina                   <=>     X1/oina),
                 m(6,  X0/ezaug/oin              <=>     X1/oina/sarrera),
                 m(9,  X0/ezaug/atzl             <=>     gehitu_listan_bukaeran(X1/ezaug/atzl, 'Gako', X2/oina/sarrera)),
                 m(10, X0/ezaug/aurl             <=>     X1/ezaug/aurl),
                 m(11, X0/ezaug/erat             <=>     '+'),
                 m(11, X0/ezaug/erat_atz         <=>     '+'),
                 m(12, X0/id                     <=>     X1/id),

                 m(14, X0/lema_osatua            <=>    $(X1/lema_osatua,      $("+", X2/lema_osatua))),
                 m(14, X0/lema_osatua_twol       <=>    $(X1/lema_osatua_twol, $("+", X2/lema_osatua_twol))),
                 m(14, X0/aldaera_osatua         <=>    osatu_aldaeraren_informazioa(X1, X2) ),
                 m(14, X0/erat                   <=>    '+'),
				     
                 m(12, X0/morf_lista             <=>     gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>     $($(X1/twolt, "+"), X2/twolt))]).



% Hitz-elkarketa
% ize-> ize + (mar + ize)
% ad.: eguzki+ (- + lore)
% Ez dugu jarri debekua 2 elkarketa egiteko. Horregatik "aditz-aspektu-marka" hitzak 2 analisi emango ditu.
% Erraza da aldatzea bakarrik bat emateko, eratorpenaren erregelan bezala ez onartzeko IZE + (IZE+IZE), hau da,
% 2 elkarketa egonez gero, beti aplikatuko da ezkerretik eskuinera
% adm ez da goratuko!!
rule(r_hitz_elkarketa, X0 ---> [X1, X2]@[
                 m(1, edo([X1/ezaug/kat      <=>    ize,
			   eta([X1/ezaug/kat <=>    adi,
			        X1/ezaug/adm badago [adize]])
			  ])),
                 m(2,  X2/ezaug/kat                           <=> marra_gehi_izena),
                 m(5,  X1/ezaug/azp                           badago [arr, zki]),  % X0 jartzen zuen! aldatuta 2005-V-31
					 
                 m(3,  X0/forma                               <=> X1/forma),
					 % ondorengo hauek banan-banan jarri behar dira
					 % bestela zirkulartasuna gertatzen delako
                 m(4,  X0/ezaug/kat                           <=>    ize),
                 m(4,  X0/ezaug/azp                           <=>    arr),
                 m(6,  X0/ezaug/plu                           <=>    X2/mugakizuna/ezaug/plu),
                 m(7,  X0/ezaug/oin                           <=>    X2/mugakizuna/ezaug/oin),
                 m(8,  X0/ezaug/atzl                          <=>    X2/mugakizuna/ezaug/atzl),
                 m(11, X0/ezaug/oinkatazp                     <=>    X2/mugakizuna/ezaug/oinkatazp),
                 % m(11, X0/ezaug/oekatazp                      <=>    X2/mugakizuna/ezaug/oekatazp),
                 m(9,  X0/ezaug/erat                          <=>    X2/mugakizuna/ezaug/erat),
                 m(10, X0/ezaug/fsl                           <=>    []),
					 % funtzio sintaktikoen lista hutsa jarriko diogu:
					 %   izena denean
					 % ADIZE denean JADNAG_MP_KM> ez goratzeko!
                 m(13, edo[eta[X2/mugakizuna/ezaug/kat        <=> ize,
			       X0/ezaug/elk                   <=> "IZE+IZE"],
			   eta[X2/mugakizuna/ezaug/kat        <=> adi,
			       X0/ezaug/elk                   <=> "IZE+ADIZE"]
			  ]),
                 m(14, X0/oina/ezaug                          <=> X0/ezaug),
                 m(15, X0/oina/elkarketa/mugakizuna/ezaug     <=> X2/mugakizuna/ezaug),
                 m(16, X0/oina/elkarketa/mugakizuna/twol      <=> X2/mugakizuna/oina/twol),
                 m(17, X0/oina/elkarketa/mugakizuna/sarrera   <=> X2/mugakizuna/oina/sarrera),
                 m(18, X0/oina/elkarketa/mugatzailea/ezaug    <=> X1/ezaug),
                 m(19, X0/oina/elkarketa/mugatzailea/twol     <=> X1/oina/twol),
                 m(20, X0/oina/elkarketa/mugatzailea/sarrera  <=> X1/oina/sarrera),
                 m(12, X0/id                                  <=> X1/id), % elkarketan lehen izenaren id-a goratuko da

	         m(12, X0/lema_osatua                         <=> $(X1/lema_osatua,      $("+", X2/lema_osatua))),
	         m(12, X0/lema_osatua_twol                    <=> $(X1/lema_osatua_twol, $("+", X2/lema_osatua_twol))),
                 m(14, X0/aldaera_osatua                      <=> osatu_aldaeraren_informazioa(X1, X2) ),
                 m(14, edo[eta[X1/erat           <=>    '+',
			       X0/erat           <=>    '+'],
			   eta[X2/erat           <=>    '+',
			       X0/erat           <=>    '+'],
			   X0/erat               <=>    '-'   
                                  % osagai bietatik bat eratorria baldin bada, orduan bai, bestela ez dago eratorpenik
			  ]),
                 m(15, X0/twolt                               <=> $($(X1/twolt, "+"), X2/twolt))]).





% Hitz-elkarketa
% ize(marraduna)-> mar + ize
% ad.: - + lore ("eguzki-lore" egiteko)
% adm ez da goratuko!
rule(r_hitz_elkarketa_marra, X0 ---> [X1, X2]@[
                 m(1, X1/ezaug/kat           <=>    mar),
                 m(2, edo([X2/ezaug/kat      <=>    ize,
			   eta([X2/ezaug/kat <=>    adi,
			        X2/ezaug/adm badago [adize]])
			  ])),
                 m(3, X2/ezaug/kas           ez     [abs, par, erg, dat, gen, gel,
		                                     soz, abu, abz, mot, ins, ala, ine, abl,
					             pro, des, adl, par]),
		% hau da, kasurik ez izatea. Hor kasu guztiak jarri nahi izan ditugu
		% horrela anbiguotasuna kentzeko 
		% (eguzki+-+lore)+a  BAI
		%( eguzki+-+(lore+a)) EZ onarzeko
                 m(4,  X0/forma                   <=> X1/forma),
                 m(5,  X0/ezaug/kat               <=> marra_gehi_izena),
                 m(6,  X0/mugakizuna/ezaug        <=> X2/ezaug),
                 m(7,  X0/mugakizuna/oina/twol    <=> X2/oina/twol),
                 m(8,  X0/mugakizuna/oina/sarrera <=> X2/oina/sarrera),
                 m(9,  X0/mugakizuna/morf_lista   <=> X2/morf_lista),
                 m(12, X0/id                      <=> X2/id),
	       
	         m(12, X0/lema_osatua             <=> $(X1/lema_osatua,      $("+", X2/lema_osatua))),
	         m(12, X0/lema_osatua_twol        <=> $(X1/lema_osatua_twol, $("+", X2/lema_osatua_twol))),
                 m(14, X0/aldaera_osatua          <=> osatu_aldaeraren_informazioa(X1, X2) ),
                 m(12, X0/erat                    <=> X2/erat),
                 m(15, X0/twolt                   <=> $($(X1/twolt, "+"), X2/twolt))]).




% Aditzoinaren gainekoak (-tea, -tzea, ...)
% Aldatua: datu_berri 2000-11-6
% Erregela honek aditza eta bere atzizkiak lotzen ditu. Ez du sortzen interpretazio berririk
% Interpretazio berriak atzizkiak lotzean sortzen dira (adib.: te+ko+tan konbinaziotik 2 intrerpretazio sortzen dira

% aditza konpl --> aditza(aditzoin) + erl (tea/tzea/konpl/helb)
% adib:  (eman+0) + te+a (ematea gustatzen zait)
% adib.: (eman+0) + te+n
% adib.: (eman+0) + te+an
% adib.: (eman+0) + te+ra+ko
% adib.: (eman+0) + te+ra+ko+an
% adib.: (eman+0) + te+ko+tan(bald)
% adib.: (eman+0) + te+ko+tan(helb)
% adib.:  izan    + ki(mod)
% SALBUESPENA: (eman+0) + te+ko(konpl/helb) HAU EZ DA EMAN BEHAR! (eman+0) + te+ko+0(konp/helb) izango da orain!
rule(r_tea_konpl, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    adi),
                 m(2,  X1/ezaug/adm        <=>    adoin),
                 m(3,  X2/ezaug/kat        <=>    erl),
                 % m(4,  X2/ezaug/azp       <=>    men), % 4.4.3n desagertuta
                                    % m(5,  X2/ezaug/erl    badago [konpl, mod, denb, helb, bald]),
				    % kendu dut, bestela ez du egiten ekar+tzerako,
				    % tzerako atzizkiak ez duelako erlaziorik adierazten
                 m(4,  edo[X2/ezaug/erlatz ez     ["teko", "tzeko"],
                           X2/ezaug/kas    badago [abs]]),  % Salbuezpena: tzeko/tzetiko + 0/a/ak(abs) 2005-VI-28
				    
                 m(6,  X0/forma            <=>    X1/forma),
                 m(7,  X0/ezaug/kat        <=>    adi),
                 m(8,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(8,  X0/ezaug/adm        <=>    X2/ezaug/adm),
                 m(8,  X0/ezaug/mug        <=>    X2/ezaug/mug),
                 m(8,  X0/ezaug/num        <=>    X2/ezaug/num),
                 m(9,  X0/oina             <=>    X1/oina),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(12, X0/erat             <=>    X1/erat),
                 m(10, X0/ezaug/erlatz     <=>    X2/ezaug/erlatz),
                 m(10, X0/ezaug/atzl       <=>    X1/ezaug/atzl),
                 m(11, X0/ezaug/aurl       <=>    X1/ezaug/aurl),
                 m(11, X0/ezaug/oinkatazp  <=>    X1/ezaug/oinkatazp),
                 m(10, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(11, X0/ezaug/erl        <=>    X2/ezaug/erl), 
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))]).






% te/tze +a = tea/tzea, 
rule(r_tze_a, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat      <=>    amm),
                 m(2,  X1/ezaug/adm      <=>    adize),
                 m(3,  X2/ezaug/kat      <=>    knmdek),
                 m(4,  X2/oina/ezaug/kas badago [abs]),
                 m(5,  X0/forma          <=>    X1/forma),
                 m(6,  X0/ezaug/kat      <=>    erl),
                 m(6,  X0/ezaug/adm      <=>    X1/ezaug/adm),
                 m(8,  X0/ezaug/erl      <=>    konpl),
                 m(9,  X0/oina           <=>    X1/oina),
                 m(10, X0/ezaug/erlatz   <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl      <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(12, X0/morf_lista     <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt          <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).



% Hiru erregela hauek (r_tzen_0, r_tzen_1 eta r_tzen_2), interpretazio batetik
% adi+te(adize)+n berri 2 sortzen dituzte: modala eta konpletiboa


/* 2006-I-19
 ERREGELA HAU EZ DA BEHAR, HORREGATIK KOMENTATU DUGU! BERE LANA R_TZE_N_2 ERREGELAK EGITEN DU, KONP ETA OBJ SORTZEN DUELAKO, HAU DA, EZ DIRA BI ELEMENTU SORTU BEHAR (BATA KONPL ETA BESTEA OBJ)
  
% ??????? 2005-XII-23 Zalantza dugu. Hau sortu behar da???????
% te/tze + n = ten/tzen (ine), 
rule(r_tze_n_0, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "n"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_OBJ"]),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).

*/


% te/tze + n = ten/tzen (modala), 
rule(r_tze_n_1, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "n"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    mod),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_ADLG"]),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).


% te/tze + n = ten/tzen (konpl), 
rule(r_tze_n_2, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "n"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    konpl),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).



% Erregela honek ez du sortzen interpretazio berririk
% adi+te(adize)+an(ine) lotzen ditu, eta denborazko mendekoa sortzen du

% te/tze + an = tean/tzean (denb), 
rule(r_tze_an, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "an"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    denb),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).



% Hiru erregela hauek (r_tzeko_0, r_tze_ko_1 eta r_tze_ko_2), interpretazio batetik
% adi+te(adize)+ko berri 2 sortzen dituzte: konpletiboa eta helburuzkoa

% te/tze + ko = teko/tzeko (izlg), 
rule(r_tze_ko_0, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "ko"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(7,  X0/oina                   <=>    X1/oina),
                 m(8,  X0/ezaug/fsl              <=>    ["@-JADNAG_MP_IZLG>"]),
                 m(9,  X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(10, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).



% te/tze + ko = teko/tzeko (konpl), 
rule(r_tze_ko_1, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "ko"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    konpl),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_OBJ"]),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).


% te/tze + ko = teko/tzeko (helb), 
rule(r_tze_ko_2, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "ko"),
                 m(5,  X0/forma                  <=>    X1/forma), 
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    helb),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_ADLG"]),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).


% teko/tzeko/tzetiko (adize-konpl)  + abs(0/a/ak) = tzekoa/ak, 
% tzeko/teko/tzetiko-ren ondoren absolutiboa bakarrik ager daiteke, horregatik erregela
% berezia jarriko dugu (bakarrik -tzeko konpletiboarekin (ez tzeko helb-rekin))
rule(r_tzeko_gehi_abs, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    erl),
                 m(3,  X1/ezaug/erl              badago [konpl, helb]),
                 m(4,  X1/ezaug/kas              <=>    gel),
                 m(5,  X2/ezaug/kat              <=>    knmdek),
                 m(6,  X2/ezaug/kas              <=>    abs),
                 m(7,  X0/forma                  <=>    X1/forma),
                 m(8,  X0/ezaug/kat              <=>    erl),
                 m(5,  X0/ezaug/mug              <=>    X2/ezaug/mug),
                 m(5,  X0/ezaug/num              <=>    X2/ezaug/num),
                 m(10, X0/ezaug/adm              <=>    adize),
                 m(11, X0/ezaug/erl              <=>    X1/ezaug/erl),
                 m(12, X0/ezaug/adoin            <=>    X1/ezaug/adoin),
                 m(13, X0/ezaug/erlatz           <=>    X1/ezaug/erlatz),
                 m(14, X0/oina                   <=>    X1/oina),
                 m(12, X0/id                     <=>    X1/id),
		 m(15, edo[eta[X1/ezaug/erl      badago [konpl],
                               X2/ezaug/mug      <=>    m,
			       X0/ezaug/fsl      <=>    ["@-JADNAG_MP_SUBJ",
							 "@-JADNAG_MP_OBJ",
							 "@-JADNAG_MP_PRED"]
			       ],
			   eta[X1/ezaug/erl      badago [konpl],
                               X2/ezaug/mug      <=> mg,
			       X0/ezaug/fsl      <=>    ["@-JADNAG_MP_OBJ"]    % "@-JADNAG_MP_ADLG" kendu dut 2005-VI-28
 			       ],
			   eta[X1/ezaug/erl      badago [helb],
			       X0/ezaug/fsl      <=>    ["@-JADNAG_MP_ADLG"]   
 			       ]
			  ]
                  ),
                 m(10, X0/ezaug/atzl      <=>    X1/ezaug/atzl),
                 m(11, X0/ezaug/aurl      <=>    X1/ezaug/aurl),
                 m(11, X0/ezaug/oinkatazp <=>    X1/ezaug/oinkatazp),
                 m(16, X0/morf_lista      <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt           <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).





% te/tze + ra = tera/tzera (helb), 
rule(r_tze_ra, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "ra"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    helb),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(9,  X0/oina                   <=>    X1/oina),  
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_ADLG"]),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).



% tera/tzera + ko = terako/tzerako
rule(r_tzera_ko, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    erl),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "ko"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(8,  X0/oina                   <=>    X1/oina),
                 m(9,  X0/ezaug/erlatz           <=>    $(X1/ezaug/erlatz, X2/oina/sarrera/'Sarrera')),
                 m(10, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_IZLG>"]),
                 m(11, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 % m(11, X0/ezaug/erl              <=>    Itsasori galdetzeko: EZ DA GORATU BEHAR!!!
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).


% terako/tzerako + 0(ABS MG) = terako/tzerako (denb), 
rule(r_tzerako_gehi_zero, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    erl),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X1/ezaug/erlatz           badago ["terako", "tzerako"]), % tzeko + 0 ez egiteko
                 m(4,  X2/ezaug/kat              <=>    dek),
                 m(5,  X2/oina/sarrera/'Sarrera' <=>    "0"),
                 m(6,  X0/forma                  <=>    X1/forma),
                 m(7,  X0/ezaug/kat              <=>    erl),
                 m(9,  X0/ezaug/erl              <=>    denb),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(10, X0/oina                   <=>    X1/oina),
                 m(11, X0/ezaug/erlatz           <=>    $(X1/ezaug/erlatz, X2/oina/sarrera/'Sarrera')),
                 m(12, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_ADLG"]),
                 m(13, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).





% terako/tzerako + an = terakoan/tzerakoan (denb), 
rule(r_tzerako_an, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    erl),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "an"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    denb),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/ezaug/erlatz, X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_ADLG"]),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).


% te/tze + rik = terik/tzerik (konpl), 
rule(r_tze_rik, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    amm),
                 m(2,  X1/ezaug/adm              <=>    adize),
                 m(3,  X2/ezaug/kat              <=>    dek),
                 m(4,  X2/oina/sarrera/'Sarrera' <=>    "ik"),
                 m(5,  X0/forma                  <=>    X1/forma),
                 m(6,  X0/ezaug/kat              <=>    erl),
                 m(8,  X0/ezaug/erl              <=>    konpl),
                 m(8,  X0/ezaug/adm              <=>    X1/ezaug/adm),
                 m(9,  X0/oina                   <=>    X1/oina),
                 m(10, X0/ezaug/erlatz           <=>    $(X1/oina/sarrera/'Sarrera', X2/oina/sarrera/'Sarrera')),
                 m(11, X0/ezaug/fsl              <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(12, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).





% teko/tzeko + rik = tekorik/tzekorik (konpl), 
rule(r_tzeko_rik, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    erl),
                 m(2,  X1/ezaug/erl              <=>    konpl),
                 m(3,  X1/ezaug/erlatz           badago ["teko", "tzeko"]),
                 m(4,  X2/ezaug/kat              <=>    dek),
                 m(5,  X2/oina/sarrera/'Sarrera' <=>    "ik"),
                 m(6,  X0/forma                  <=>    X1/forma),
                 m(7,  X0/ezaug/kat              <=>    erl),
                 m(9,  X0/ezaug/erl              <=>    konpl),
                 m(10, X0/oina                   <=>    X1/oina),
                 m(11, X0/ezaug/erlatz           <=>    $(X1/ezaug/erlatz, X2/oina/sarrera/'Sarrera')),
                 m(12, X0/ezaug/fsl              <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(13, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).




% Bi erregela hauek (r_tzeko_tan_1 eta r_tzeko_tan_2), interpretazio batetik
% adi+te(adize)+ko+tan 2 sortzen dituzte: konpletiboa eta helburuzkoa

% teko/tzeko + tan = tekotan/tzekotan (helb), 
rule(r_tzeko_tan_1, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    erl),
                 m(2,  X1/ezaug/erl              <=>    konpl),
                 m(3,  X1/ezaug/erlatz           badago ["teko", "tzeko"]),
                 m(4,  X2/ezaug/kat              <=>    dek),
                 m(5,  X2/oina/sarrera/'Sarrera' <=>    "tan"),
                 m(6,  X0/forma                  <=>    X1/forma),
                 m(7,  X0/ezaug/kat              <=>    erl),
                 m(9,  X0/ezaug/erl              <=>    helb),
                 m(10, X0/oina                   <=>    X1/oina),
                 m(11, X0/ezaug/erlatz           <=>    $(X1/ezaug/erlatz, X2/oina/sarrera/'Sarrera')),
                 m(12, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_HELB"]),
                 m(13, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).


% teko/tzeko + tan = tekotan/tzekotan (bald), 
rule(r_tzeko_tan_2, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat              <=>    erl),
                 m(2,  X1/ezaug/erl              <=>    konpl),
                 m(3,  X1/ezaug/erlatz           badago   ["teko", "tzeko"]),
                 m(4,  X2/ezaug/kat              <=>    dek),
                 m(5,  X2/oina/sarrera/'Sarrera' <=>    "tan"),
                 m(6,  X0/forma                  <=>    X1/forma),
                 m(7,  X0/ezaug/kat              <=>    erl),
                 m(9,  X0/ezaug/erl              <=>    bald),
                 m(10, X0/oina                   <=>    X1/oina),
                 m(11, X0/ezaug/erlatz           <=>    $(X1/ezaug/erlatz, X2/oina/sarrera/'Sarrera')),
                 m(12, X0/ezaug/fsl              <=>    ["@-JADNAG_MP_BALD"]),
                 m(13, X0/morf_lista             <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt                  <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).




% Erregela honek aditza eta "te/tze" atzizkia lotzen ditu.
% Bakarrik ekar+tze modukoak egingo ditu, bestela ekar+(tze+n) egiten direlako, hau da,
% lehenengo atzizkiak lotu eta ondoren aditzarekin

% adib:  ekar+tze
rule(r_tze_adize, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    adi),
                 m(2,  X2/ezaug/kat        <=>    amm),
                 m(3,  X2/ezaug/adm        <=>    adize),
                 m(4,  X0/forma            <=>    X1/forma),
                 m(5,  X0/ezaug/kat        <=>    adi),
                 m(6,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(8,  X0/ezaug/adm        <=>    X2/ezaug/adm),
                 m(7,  X0/oina             <=>    X1/oina),
                 m(8,  X0/ezaug/aurl       <=>    X1/ezaug/aurl),
                 m(9,  X0/ezaug/fsl        <=>    ["@-JADNAG_MP_KM>"]),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(12, X0/erat             <=>    X1/erat),
                 m(10, X0/ezaug/atzl       <=>    X1/ezaug/atzl),
                 m(11, X0/ezaug/oinkatazp  <=>    X1/ezaug/oinkatazp),
                 m(10, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).



% ekartze(adize) + ari/arekin ...
% genitiboa ez da erregela honekin tratatuko
rule(r_tze_gehi_knmdek, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat      <=>    adi),
                 m(2,  X1/ezaug/adm      badago [adize]),
                 m(3,  X1/ezaug/erl      ez     [denb, konpl, helb, mod, kaus, bald]),
                 m(4,  X2/ezaug/kat      <=>    knmdek),
		 m(5,  X1/ezaug/kas_plus ez     ["abl_gel", "abu_gel", "soz_gel", "pro_gel"]),
		                % ekartzetiko(adize)+a ez egiteko (r_lehen_knmdek_arrunta-k egiten du)
                 m(5,  X2/ezaug/kas      ez     [mot, gel]),
				% ekartze+agatik beste erregela batek egiten du (r_adi_gatik)
                 m(6,  edo[X2/ezaug/kas  ez     [abs, par, ine, ala],  % gel onartuko da 2005-VI-28
				% ekartze + a/ak/rik(abs/par) beste erregela batek (r_tze_a/r_tze_rik + r_tea_konpl)
				% ekartze + n(ine) beste erregela batek (r_tze_n_1/2 gehi r_tea_konpl)
				% ekartze + ra(ala) beste erregela batek (r_tze_ra gehi r_tea_konpl, helburuzkoa sortzeko)
                           X1/ezaug/kas  badago [gen]
			                  % Hauek ez dute kasuistika berezirik sortzen, te+a, te+n, .. eta horiek bezala.
					  % ekartzearen + a/ak 
			                  % ekartzearen + 0 
			                  % ekartzearen + (0+ean/era/...) 
			  ]),
                 m(7,  X0/forma            <=>    X1/forma),
                 m(8,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(9,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(5,  X0/ezaug/mug        <=>    X2/ezaug/mug),
                 m(5,  X0/ezaug/num        <=>    X2/ezaug/num),
                 m(8,  X0/ezaug/adm        <=>    X1/ezaug/adm),
                 m(10, X0/oina             <=>    X1/oina),
                 m(12, X0/ezaug/oin        <=>    X1/ezaug/oin),
                 m(13, X0/ezaug/atzl       <=>    X1/ezaug/atzl),
                 m(14, X0/ezaug/aurl       <=>    X1/ezaug/aurl),
                 m(11, X0/ezaug/oinkatazp  <=>    X1/ezaug/oinkatazp),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(12, X0/erat             <=>    X1/erat),
                 m(15, X0/ezaug/fsl        <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(16, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).




% Erregela berria 2005-VI-28
% dela(adl/adt) + ko
% dela+ko + 0(abs mg)
rule(r_dela_ko, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        badago [adl, adt]),
                 m(2,  X1/ezaug/erl        badago [konpl]),
                 m(4,  X2/ezaug/kat        <=>    knmdek),
                 m(7,  X0/forma            <=>    X1/forma),
                 m(8,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(9,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(5,  X0/ezaug/mug        <=>    X2/ezaug/mug),
                 m(5,  X0/ezaug/num        <=>    X2/ezaug/num),
                 m(10, X0/oina             <=>    X1/oina),
                 m(12, X0/ezaug/oin        <=>    X1/ezaug/oin),
                 m(13, X0/ezaug/atzl       <=>    X1/ezaug/atzl),
                 m(14, X0/ezaug/aurl       <=>    X1/ezaug/aurl),
                 m(11, X0/ezaug/oinkatazp  <=>    X1/ezaug/oinkatazp),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(12, X0/erat             <=>    X1/erat),
                   % 2005-VI-29: bereizteko ea laguntzailea ala nagusia den:
                 m(15, edo[eta[X1/ezaug/kat       <=> adl,
                               X0/ezaug/fsl       <=> gehitu_aurrizkia("@+JADLAG_MP_", X2/ezaug/fsl)
                              ],
                           eta[X1/ezaug/kat       <=> adt,
                               X0/ezaug/fsl       <=> gehitu_aurrizkia("@+JADNAG_MP_", X2/ezaug/fsl)
                              ]
                          ]),
                 m(16, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))
            ]).




% Berria 2005-VI-30
% de + lako(kaus) kasu berezia da, etiketa berria sortu behar delako: @+JADNAG_MP_ADLG/@+JADLAG_MP_ADLG
%    dakite+la(mod/denb), dakite+nean (denb), dakite+neko (denb), dakite+larik (mod/denb), da + ino(denb)
rule(r_adl_adt_gehi_erl_adlg, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat             badago [adl, adt]),
                 m(2,  X2/ezaug/kat             <=>    erl),
                 m(2,  X2/oina/ezaug/erl badago [kaus, denb, helb, mod, mos, 'mod/denb']), 
                            % kaus/denb/mod/helb/mos? (de+lako) salbuespena da, @+JADNAG_MP_ADLG sortu behar delako 2005-VI-30
                 m(4,  X0/forma                 <=>    X1/forma),
                 m(5,  X0/ezaug/kat             <=>    X1/ezaug/kat),
                 m(6,  X0/oina                  <=>    X1/oina),
                 m(12, X0/id                    <=>    X1/id),
                 m(14, X0/lema_osatua           <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol      <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua        <=>    X1/aldaera_osatua ),
                 m(12, X0/erat                  <=>    X1/erat),
                 m(11, X0/ezaug/erlatz          <=>    X2/oina/sarrera/'Sarrera'), % 2005-I-20 Bereizteko zein atziki den! 
                 m(7,  X0/morf_lista            <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                   % 2005-VI-29: bereizteko ea laguntzailea ala nagusia den:
                 m(15, edo[eta[X1/ezaug/kat     badago [adl],
                               X0/ezaug/fsl     <=>    ["@+JADLAG_MP_ADLG"]
                              ],
                           eta[X1/ezaug/kat     badago [adt],
                               X0/ezaug/fsl     <=>    ["@+JADNAG_MP_ADLG"]
                              ]
                          ]),
                 m(11, X0/ezaug/erl             <=>    X2/ezaug/erl), 
                 m(15, X0/twolt                 <=>    $($(X1/twolt, "+"), X2/twolt))]).






% ekartzearentzat + ko
% ekartzetik      + ko
% ekartzearekin   + ko
% ekartzeraino    + ko
% ekartzeranz     + ko ??????? Hau uste dut ezin dela gertatu (adize-rekin, eratorpenaren bidez bai posiblea delako)
rule(r_tze_gehi_ko_izenlagunetan, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    adi),
                 m(2,  X1/ezaug/adm        badago [adize]),
		 m(3,  X1/ezaug/erl        ez     [denb, konpl, helb, mod, kaus, bald]),
                 m(4,  X1/ezaug/kas        badago [soz, abu, abl, pro]),
                 m(5,  X0/forma            <=>    X1/forma),
                 m(6,  X2/ezaug/kat        <=>    dek),
                 m(7,  X2/ezaug/kas        badago [gel]),
                 m(8,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(8,  X0/ezaug/adm        <=>    X1/ezaug/adm),
    
                 m(9,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(10, X0/oina             <=>    X1/oina),
                 m(11, X0/ezaug/oin        <=>    X1/ezaug/oin),
                 m(12, X0/ezaug/atzl       <=>    X1/ezaug/atzl),
                 m(12, X0/ezaug/aurl       <=>    X1/ezaug/aurl),
                 m(11, X0/ezaug/oinkatazp  <=>    X1/ezaug/oinkatazp),
                 m(13, X0/ezaug/kas_plus   <=>    $($(X1/ezaug/kas, "_"), X2/ezaug/kas)),
			% JM+Koldok asmatuta: tzetiko(abl_gel), tzerainoko(abu_gel), tzearekiko(soz_gel)
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(12, X0/erat             <=>    X1/erat),
		 m(14, X0/ezaug/fsl        <=>    gehitu_aurrizkia("@-JADNAG_MP_", X2/ezaug/fsl)),
                 m(15, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))
          ]).


% bai/ez(prt) + etz(erl-konpl)
rule(r_bai_etz, X0 ---> [X1, X2]@[
                 m(1,  X1/ezaug/kat        <=>    prt),
                 m(2,  X1/ezaug/mod        <=>    egi),
                 m(3,  X2/ezaug/kat        <=>    erl),
                 m(5,  X2/ezaug/erl        <=>    konpl),
                 m(6,  X0/forma            <=>    X1/forma),
                 m(7,  X0/ezaug/kat        <=>    X1/ezaug/kat),
                 m(8,  X0/ezaug/azp        <=>    X1/ezaug/azp),
                 m(9,  X0/oina             <=>    X1/oina),
                 m(10, X0/ezaug/oin        <=>    X1/ezaug/oin),
                 m(12, X0/id               <=>    X1/id),
                 m(14, X0/lema_osatua      <=>    X1/lema_osatua ),
                 m(14, X0/lema_osatua_twol <=>    X1/lema_osatua_twol ),
                 m(14, X0/aldaera_osatua   <=>    X1/aldaera_osatua ),
                 m(12, X0/erat             <=>    X1/erat),
                 m(11, X0/morf_lista       <=>    gehitu_morf_lista(X1/morf_lista, X2/morf_lista)),
                 m(11, X0/ezaug/erl        <=>    X2/ezaug/erl), 
                 m(15, X0/twolt            <=>    $($(X1/twolt, "+"), X2/twolt))
				 ]).










/* erregela honek bukaerako post-tratamendua egingo du, gehienbat
   osagaien antolaketa: elipsirik ez dagoenean ez da lortzen osagaien segida,
   osagai bakarra dagoelako. Dena den, emaitzan osagai BAT dagoela adierazi behar da.
   Horregatik erregela honek hori egingo du:
     - osagaien zerrenda baldin bazegoen, emaitza dagoen bezala utzi
     - ez badago osagaien zerrenda, orduan osagai bakarreko zerrenda sortu
*/

rule_post(erregela_post, X0 ---> [X1]@
                [m(00, XX/goimailakoezaug/kat              <=> X1/ezaug/kat),
		 m(00, XX/goimailakoezaug/azp              <=> X1/ezaug/azp),
		 m(00, XX/goimailakoezaug/mai              <=> X1/ezaug/mai),
		 m(00, XX/goimailakoezaug/biz              <=> X1/ezaug/biz),
		 m(00, XX/goimailakoezaug/zenb             <=> X1/ezaug/zenb),
		 m(00, XX/goimailakoezaug/neur             <=> X1/ezaug/neur),
		 m(00, XX/goimailakoezaug/plu              <=> X1/ezaug/plu),
		 m(00, XX/goimailakoezaug/izaur            <=> X1/ezaug/izaur),
		 m(00, XX/goimailakoezaug/adm              <=> X1/ezaug/adm),
		 m(00, XX/goimailakoezaug/lagm             <=> X1/ezaug/lagm),
		 m(00, XX/goimailakoezaug/azperd           <=> X1/ezaug/azperd),
		 m(00, XX/goimailakoezaug/adbm             <=> X1/ezaug/adbm),
		 m(00, XX/goimailakoezaug/per              <=> X1/ezaug/per),
		 m(00, XX/goimailakoezaug/nmg              <=> X1/ezaug/nmg),
		 m(00, XX/goimailakoezaug/hurb             <=> X1/ezaug/hurb),
		 m(00, XX/goimailakoezaug/pos              <=> X1/ezaug/pos),
		 m(00, XX/goimailakoezaug/mtkat            <=> X1/ezaug/mtkat),
		 m(00, XX/goimailakoezaug/adr              <=> X1/ezaug/adr),
		 m(00, XX/goimailakoezaug/asp              <=> X1/ezaug/asp),
		 m(00, XX/goimailakoezaug/erl              <=> X1/ezaug/erl),
		 m(00, XX/goimailakoezaug/klm              <=> X1/ezaug/klm),
		 m(00, XX/goimailakoezaug/kas              <=> X1/ezaug/kas),
		 m(00, XX/goimailakoezaug/num              <=> X1/ezaug/num),
		 m(00, XX/goimailakoezaug/mug              <=> X1/ezaug/mug),
		 m(00, XX/goimailakoezaug/fsl              <=> X1/ezaug/fsl),
		 m(00, XX/goimailakoezaug/mod              <=> X1/ezaug/mod),
		 m(00, XX/goimailakoezaug/kas_plus         <=> X1/ezaug/kas_plus),
		 m(00, XX/goimailakoezaug/rare             <=> X1/ezaug/rare),

		 m(00, XX/goimailakoezaug/oinkatazp        <=> X1/ezaug/oinkatazp),
		 m(00, XX/goimailakoezaug/oekatazp         <=> X1/ezaug/oekatazp),
		 m(00, XX/goimailakoezaug/oin              <=> X1/ezaug/oin),
		 m(00, XX/goimailakoezaug/atzl             <=> X1/ezaug/atzl),
		 m(00, XX/goimailakoezaug/aurl             <=> X1/ezaug/aurl),
		 m(00, XX/goimailakoezaug/osa1             <=> X1/ezaug/osa1),
		 m(00, XX/goimailakoezaug/osa2             <=> X1/ezaug/osa2),
		 m(00, XX/goimailakoezaug/elk              <=> X1/ezaug/elk),

		 m(00, XX/goimailakoezaug/mdn              <=> X1/ezaug/mdn),
		 m(00, XX/goimailakoezaug/nor              <=> X1/ezaug/nor),
		 m(00, XX/goimailakoezaug/nork             <=> X1/ezaug/nork),
		 m(00, XX/goimailakoezaug/nori             <=> X1/ezaug/nori),
		 m(00, XX/goimailakoezaug/hit              <=> X1/ezaug/hit),

		 m(00, XX/goimailakoezaug/adoin            <=> X1/ezaug/adoin),
		 m(00, X0/id                               <=> X1/id),
                 % ezaugarriak ordenatu egin dira XX aldagaian!!!

		 m(00, X0/aldaera_osatua                   <=> X1/aldaera_osatua),
		 % m(00, X0/kk                               <=> X1/lema_osatua),

                 m(00, edo[eta[X1/erat                 badago ['+'],
			       X0/lema_osatua          <=>       X1/lema_osatua_twol % eratorpena baldin badago, orduan 2 mailatako formak
			      ],
		           X0/lema_osatua              <=>       X1/lema_osatua      % bestela lema arrunta
			  ]),

		 m(1,  edo[eta [X1/osagai_lista        definitua, % elipsia dagoenean osagaien lista sortua dago
				X0/forma               <=>       X1/forma,
				X0/goimailakoezaug     <=>       XX/goimailakoezaug,
				X0/oina                <=>       X1/oina,
				X0/osagai_lista        <=>       X1/osagai_lista],

			   % kasu honetan osagai bakarra dago, eta osagai normala da (lema bat)
			    eta[ X1/ezaug/kat          ez        [dek, amm, asp, erl, gra, eli],   % lema bat da
				 X0/forma              <=>       X1/forma,
				 X0/goimailakoezaug    <=>       XX/goimailakoezaug,
				 Osagai_bat/oina       <=>       X1/oina,
				 
				 % Osagai_bat/ezaug      <=> X1/ezaug, % 2004-VII-6 Osagai bakarrekoekin ez,
				                                       %            informazioa errepikatzen delako (goi-mailako ezaugarriak)
				 Osagai_bat/morf_lista <=>       X1/morf_lista,
				 Osagai_bat/twolt      <=>       X1/twolt,		
				 X0/osagai_lista       <=>       [osagaia(Osagai_bat)]
			       ],

			   % kasu honetan osagai bakarra dago, baina ez da lema bat (adib.: "bait"[kat:erl])
			   % Hemen ez da goratu behar "oina", azkenean horren informazioa morfemen listan egongo delako
			    eta[ X1/ezaug/kat          badago    [dek, amm, asp, erl, gra, eli],   % morfema bat da
				 X0/forma              <=>       X1/forma,
				 X0/goimailakoezaug    <=>       X1/ezaug,

				 % Osagai_bat/oina       <=> X1/oina,
	
				 Osagai_bat/morf_lista <=>       X1/morf_lista,
				 Osagai_bat/twolt      <=>       X1/twolt,		
				 X0/osagai_lista       <=>       [osagaia(Osagai_bat)]
			       ]
			  ])
		]).
