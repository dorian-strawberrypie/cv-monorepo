= Duel Heores (zadání Karetní RPG)
Autor: Jakub Dorian Charbulák

== Zadání

Naprogramujte engine pro hraní karetního RPG

Váš engine:

. ze souboru nahraje definici karet (jejich typ, atributy, efekty), balíčku (seznam karet v balíčku)
. umožní vytvořit a hrát samotnou karetní hru
. implementuje variantu pro jednoho hráče proti počítači (náhodné tahy nestačí)
. implementuje variantu pro dva hráče (výměna přes potvrzovací okno, aby soupeř neviděl karty, nebo naopak soupeři si celou dobu do karet vidí)
. umožňuje ukládat a načítat rozehrané hry

Kde lze využít polymorfismus? (doporučené)

. Typy karet: útočné, obranné, speciální, ...
. Efekty akcí: síla útoku, síla obrany, vem si X karet, zahoď X karet
. Ovládání hráče: lokální hráč, umělá inteligence (různé druhy), síťový hráč
. Uživatelské rozhraní: konzole, ncurses, SDL, OpenGL (různé varianty), ...

Ukázky:

http://jadropudla.cz/hitstick/

https://cs.wikipedia.org/wiki/Bang!_(hra)

== Specifikace

Duel Heroes je inspirovaná například hrou Hitstick, hrajete za zvoleného hrdinu proti jinému hrdinovi
Spuštění hry probíhá následovně:
1. Uživatel otevře konzolovou aplikaci
2. Vybere soubor s definicemi karet a postav
3. Zvolí zda si přeje hrát proti ai, nebo lokální multiplayer
4. Spustí hru
   
NEBO
2. Nahraje hru ze savefile
- postava bude oběma hráčům vybrána náhodně, jako ve hře Bang!

Pravidla a průběh hry:
1. Každý hráč má k dispozici 6 hracích karet
   . ty mohou být útočné, nebo buff
2. Tahem hráče je zahrání, nebo zahození právě jedné karty, poté tah končí
3. Hráč musí vždy buď zahrát nebo zahodit právě jednu kartu
4. Karta je mu při dalším kole doplněna, náhodně
5. Hra končí, když jedna strana zničí druhou (životy na 0), nebo když získá 100 zlatých - tím vyhraje

Mechaniky hry:
1. každá postava má jiné vlastnosti:
   . životy, peníze, mana, stamina, štít, regenerace (každý tah, zvlášť je reg. pro peníze, manu a staminu)
2. každá karta má definovaný:
   . efekt (např. +10 životů)
   . cenu (např. -5 stamina, nejspíše také implementuji jako efekt)
   . cíl efektu (sebe, nepřítele, všechny) - povinně def.

Features:
- hra proti ai
- 2p multiplayer
- definice postav, karet a balíčku ze souboru (ve formátu později specifikovaném)
- načítání a ukládání her

Ovládání:
- v cyklu třídy CApplication (něco jako menu), bude moci uživatel použít příkazy CCommandApp:
  start - zapoceti nové hry
  config - zobrazí uživateli konfiguraci
  mode <name> - nastavení módu hry na "versus" (hru dvou hráčů), nebo "ai" (hru proti počítači)
  load <savename> - načte hru ze souboru s názvem savefile
  setpack <type> <filename> - type bude buď "action" pro nahrání akčních, nebo "character" pro nahrání karet postav.
  exit - opuštění aplikace
- help - vypíše commands

- uvnitř cyklu aplikace bude cyklus pod CGame, ve kterém budou příkazy:
  throw <cardNumber> - zahodi kartu
  play <cardNumber> - zahraje kartu
  save <filename> - ulozi hru pod zadanym nazvem do složky gamesavea
  exit - opustit aplikaci
- help - vypíše commands

Balíčky karet:
Akční balíčky se nachází v podsložce examples/cardpacks/actionpacks. Jejich formát je následující:

    count X; (X je int)
    name CARDNAME;
    effect EFFECTTYPE; ("buff"/"attack", ~0..*~ efektů)
    ...

    atributy jsou až na efekt povinné, v daném pořadá. Chceme-li aby karta měla nějaký efekt, musíme mu jí přidat..
    - pro efekt attack:
    ...
    target TARGET; ("self"/"enemy")
    damage DAMAGE; (int)
    criticalChance CC; (v %, int)
    criticalDamage CD; (int)

    - pro efekt buff:
    target TARGET; ("self"/"enemy")
    health X;
    stamina X;
    staminaGain X;
    mana X;
    manaGain X;
    gold X;
    goldGain X;
    shield X;, X jsou vždy int
    - atributy, na které se efekt nevztahuje, lze vynechat, ale je třeba zachovat pořadí.

    Character balíčky se nacházejí v podsložce examples/cardpacks/actionpacks. Jejich formát je následující:

    name CARDNAME;
    maxHealth X;
    stamina X;
    staminaGain X;
    mana X;
    manaGain X;
    gold X;
    goldGain X;

    Je třeba zachovat vyplňované pořadí atributů, X je celé číslo.

== Polymorfismus

Polymorfismus je aplikován v rámci hierarchií tříd CPlayer, CCard, CEffect.

Player má dva potomky CPlayerHuman a CPlayerAI. Třída Player má polymorfní metodu turn(), která od konkrétního hráče vyžádá tah kartou (buď zahrání, nebo zahození). Implementace pro uživatele očekává jeho vstup, implementace AI táhne v závislosti na aktuální situaci. K polymorfnímu volání dochází při každém tahu některého z hráčů, kdy se pokaždé dotážeme na tah obecného hráče CPlayer. Polymorfismus zde nám pomůže hlavně v tom, že pro přidání nové ai, síťového hráče, nebo úplně jiného typu hráče stačí vytvořit nového potomka třídy CPlayer.

CCard má potomky CCardCharacter a CCardAction. Bude zajišťovat, mimo jiné, vyobrazení karet v UI. Polymorfismus se uplatní v metodách: stringCard() pro vypsání karty.

CEffect implementuje efekty karet třídy CCardAction. Typy efektu budou CEffectBuff a CEffectAttack. Jedna karta bude mít vektor s CEffect isntancemi. Polymorfismus se projeví aplikováním efektu, tedy, když ji hráč zahraje - apply(), dále v hasSufficientAttr() . zjistí zda má hráč dost atributů na použití efektu, nebo ve stringEffect() - stringove repr. efektů.