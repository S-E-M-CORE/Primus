die grafische Übersicht findes du hier [[ER_Model_Primus_PNG.excalidraw.png]]
## Beziehungen zwischen den Entitäten

- Ein Mitglied kann in mehreren Abteilungen sein, aber die Mitgliedschaft in einer bestimmten Abteilung ist eindeutig.
    - Beziehung zwischen Mitglieder und Mitgliedschaft: 1:N
    
- Jede Abteilung hat mehrere Mitglieder, aber jedes Mitglied ist nur in einer Abteilung.
    - Beziehung zwischen Abteilungen und Mitgliedschaft: 1:N
    
- Jedes Mitglied kann mehrere Kontaktinformationen und Adressen haben.
    - Beziehung zwischen Mitglieder und Kontaktinformationen/Adresse: 1:N
    
- Ein Mitglied kann an mehreren Trainingseinheiten teilnehmen, aber jede Trainingseinheit gehört zu einer Abteilung.
    - Beziehung zwischen Mitglieder und Trainingsteilnahme: 1:N
    - Beziehung zwischen Abteilungen und Trainingsteilnahme: 1:N
    
- Der Waffenerwerb hängt von den Mitgliedschaftsdaten und der Trainingsteilnahme ab.
    - Beziehung zwischen Mitglieder, Mitgliedschaft und Waffenerwerb: 1:N
    - Beziehung zwischen Mitglieder, Trainingsteilnahme und Waffenerwerb: 1:N