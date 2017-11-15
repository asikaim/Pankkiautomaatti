# Pankkiautomaatti
1. Ongelma

Yksinkertainen pankkiautomaatti, joka tulostaa ainoastaan 20e ja 50e seteleitä. Ohjelma lukee käyttäjän pinkoodin tekstitiedostosta, ja mikäli syötetty pinkoodi on väärä, ohjelma ei päästä käyttäjää palveluihin. Ohjelmassa on perus pankkiautomaattipalvelut, eli rahan nosto, tilin saldo ja talletus (joka ei perinteisesti pankkiautomaateista löydy, mutta joissakin paikoissa se on mahdollisuus).

2. Ratkaisut

Lähdin aluksi rakentamaan automaattia pelkkään mainfunktioon, mutta myöhemmin tajusin, että testauksen ja toteutuksen kannalta on helpompaa luoda jokainen osio eri funktioon. Ohjelman algoritmi menee (karkeasti) seuraavasti:

PÄÄFUNKTIO
1. lue tilinumero
2. tarkastaa löytyykö tilinumerolla tekstitiedostoa
3. JOS tilinumero löytyy
4. 	syötä pinkoodi
5.		JOS pinkoodi sama kuin tekstitiedostossa
6. 			Avaa päävalikko
7.			VALINTA 1, 2, 3 tai 4
8.		MUUTEN PRINT ”pinkoodi virheellinen”
9. MUUTEN PRINT ”tili suljettu”

PÄÄVALIKKO
1. PRINT ”1. nosto”
2. PRINT ”2. talletus”
3. PRINT ”3. tilin saldo”
4. PRINT ”4. lopetus”
5. kysy valinta

NOSTO
1. nostomäärä = 0
2. kakskymppiset = 0
3. viiskymppiset = 0
4. PRINT ”paljonko nostetaan”
5. nostomäärä = lueKokonaisluku
6. JOS nostomäärä <= saldo
7.		JOS nostomäärä < 20 TAI nostomäärä = 30
8.			PRINT ”virheellinen määrä”
9.	 MUUTEN JOS nostomäärä % 10 = 0
10.		saldo = saldo – nostomäärä
11.		KUN nostomäärä > 0
12.			JOS nostomäärä % 50 = 0
13.				viiskymppiset = viiskymppiset + 1
14.				nostomäärä = nostomäärä – 50
15.			MUUTEN JOS nostomäärä % 20 = 0
16.				kakskymppiset = kakskymppiset + 1
17.				nostomäärä = nostomäärä – 20
18.			MUUTEN
19.				viiskymppiset = viiskymppiset + 1
20.				nostomäärä = nostomäärä – 50
21.		 MUUTEN
22.			PRINT ”virheellinen määrä”
23.	 PRINT viiskymppiset
24.	 PRINT kakskymppiset
25.	 PRINT saldo
26. PRINT ”tilillä ei tarpeeksi rahaa”
27. PRINT saldo

TALLETUS
1. lisää = 0
2. PRINT ”paljonko talletetaan”
3. lisää = lueKokonaisluku
4. saldo = saldo + lisää

NYKYINEN SALDO
1. print saldo

TOISTO
1.  PRINT ”haluatko tehdä toisen siirron”
2.  PRINT ”Valitse (K)yllä tai (E)i”
3. LUE vastaus

Ohjelmasta löytyvät funktiot:
Main -funktio (Tarkastaa tilinumeron ja pinkoodin, avaa päävalikon ja tarkastaa käyttäjän valinnat)
paaValikko (Näyttää käyttäjälle automaatin vaihtoehdot)
nosto (Kysyy nostettavan rahan määrän, tallettaa nykyisen saldon ja laskee annettavat setelit)
talletus (Kysyy talletuksen määrän ja päivittää nykyisen saldon)
nykySaldo (Näyttää nykyisen saldon)
toisto (Kysyy käyttäjältä haluaako tämä tehdä toisen siirron)

Lisäksi käytin harjoituksista tuttuja lueKokonaisluvut ja lueRoskat -funktioita.
Ohjelmassa käytetyt tiedostot ovat itse automaattiohjelma ja 12345.tili tiedosto, jossa on tilinumero sekä pinkoodi.

3. Käyttöohjeet

Ensimmäisenä käyttäjän tulee syöttää tilinumero ja jos tilinumero löytyy automaatin tekstitiedostosta, ohjelma kysyy pinkoodia. Tilinumero ja pinkoodi voivat molemmat olla maksimissaan 256 merkkiä pitkiä. Tämän jälkeen aukeaa päävalikko, jossa on vaihtoehdot 1. Nosto 2. Talletus 3. Nykyinen Saldo ja 4. Lopetus. Jokaisen toiminnon jälkeen automaatti kysyy haluaako käyttäjä toistaa noston tai talletuksen. Mikäli käyttäjä valitsee ”Ei” voi käyttäjä palata automaatin alkuvalikkoon ja valita ”Lopetus” tai jonkin toisen ominaisuuden.

Nostaessa rahaa automaatti voi antaa ainoastaan 20e ja 50e seteleitä. Automaatti vähentää nostettavat rahat tilin saldosta ja jos käyttäjällä on vähemmän rahaa kuin käyttäjä antaa nostomääräksi, nostoa ei tapahdu. Käyttäjä voi nostaa 20e tai 40e ja tästä eteenpäin 10e välein. Noston jälkeen automaatti näyttää tilin nykyisen saldon käyttäjälle.

Talletuksen avulla käyttäjä voi lisätä rahaa tililleen. Nykyinen saldo näyttää käyttäjän tämän hetkisen rahamäärän tilillä.

4. Testaus

Ensimmäisenä testaan reagoiko ohjelma odotetusti, mikäli tilitiedostossa on ongelmia tai tilinumero ja pinkoodi ovat virheellisiä. Kokeilin ohjelmaa ilman tilitiedostoa, 12345 pinkoodilla ja 123456 tilinumerolla. Ohjelma toimi odotetusti eikä päästänyt käyttäjää käsiksi automaatin funktioihin. 

Toiseksi testaan päävalikon toimivuuden, mikäli käyttäjä valitsee jonkin muun numeron, kuin 1-4. Kokeilin numeroa 7. Ohjelma syöttää näytölle viestin ”virheellinen valinta,” mutta toistofunktio kuitenkin kysyy tarpeettomasti haluaako käyttäjä uusia virheellisen valinnan.

Kolmanneksi testaan nostofunktion. Käyttäjän ei ole mahdollista nostaa enempää rahaa kuin tilillä on. Kokeilin tätä luvulla 100. Lisäksi käyttäjä ei voi nostaa virheellisiä lukumääriä. Tätä kokeiltiin luvuilla 19, 30, 10, 9 ja 290.5. En saanut ohjelmassa ylivuotoa aikaiseksi syöttämällä liian suuria numeroita (kokeilin luvulla 99999999999999999999999). Funktion normaalia toimivuutta kokeiltiin luvulla 80, ja ohjelma syötti neljä kahden kympin seteliä, sekä poisti 80e tililtä. 

Toistofunktio toimii oikein nostotilanteissa, mutta edellinen tapahtuma toistetaan, mikäli käyttäjä kirjoittaa mitä tahansa muuta kuin E tai e. Periaatteessa toisto toimii siis aivan oikein, mutta funktiota olisi voinut muokata antamaan virhe ilmoituksen, mikäli käyttäjä ei vastaa K/k tai E/e.

Neljäntenä testaan talletusfunktion toimivuuden. Kokonaisluvut tallettuvat normaalisti tilille (kokeitlu luvulla 100), mutta esim. 0.5 ei ole mahdollinen talletus. Suurien rahamäärien talletus aiheuttaa ylivuototilanteen. Yritin tallettaa 999999999999999999999999999999 euroa tilille ja tilin saldoksi muuttui 8e. Tämä on vakava ongelma, jonka korjaamiseksi en löytänyt ratkaisua ilman ohjelman toiminnan rajoittamista.

Toistofunktio toimii talletusfunktion kanssa tuttuun tapaan jokaisessa eri testissä.
