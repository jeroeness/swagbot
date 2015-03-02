RP6 Software
=======================

De ontwikkeling van de RP6 software gebeurt hier.

Elk stuk code dat hiernaartoe gepusht wordt, moet in het juiste bestand staan. We willen spaghetticode voorkomen.
Zo is er voor de aansturing van de motor één bestand aangemaakt, waarin alle motorfuncties komen te staan. 

Om al deze code te compileren en daar één (naar de RP6 uploadbaar-)bestand van te maken is er de Makefile. Het enige wat je hoeft te doen om jouw bestand op te laten nemen in de compilatie is de naam (+ext.) in de makefile op te nemen onder 'OTHER_SOURCES'.

Aangezien we geen zin hebben om deze Makefile continu aan te passen zetten we alle functieprototypes wel in één bestand, namelijk 'func_protos.h'. Dit doe je echter wel onder het bijpassende comment dat aangeeft voor welk bestand er prototypes komen. Overigens is dit een goede plek om je geschreven functies te documenteren.
