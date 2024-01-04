1. **Mitglieder:**
    - Attribute: MitgliederID (Primärschlüssel), Vorname, Nachname, Geburtsdatum, 
    
1. **Angestellte:**
    - Attribute: AngestellteID (Primärschlüssel), Name, Position, 

1. **Abteilungen:**
    - Attribute: AbteilungsID (Primärschlüssel), Name, Beitrag pro Monat, ...
    
1. **Mitgliedschaft:**
    - Attribute: MitgliedschaftID (Primärschlüssel), MitgliederID (Fremdschlüssel zu Mitglieder), AbteilungsID (Fremdschlüssel zu Abteilungen), Mitgliedsbeitrag (monatlich), ...
    
1. **Kontaktinformationen:**
    - Attribute: KontaktID (Primärschlüssel), MitgliederID (Fremdschlüssel zu Mitglieder), Telefonnummer, Handynummer, E-Mail, Messenger Service, ...
    
1. **Adresse:**
    - Attribute: AdresseID (Primärschlüssel), MitgliederID (Fremdschlüssel zu Mitglieder), Straße, Hausnummer, PLZ, Ort, Bundesland, ...
    
1. **Trainingsteilnahme:**
    - Attribute: TrainingID (Primärschlüssel), MitgliederID (Fremdschlüssel zu Mitglieder), AbteilungsID (Fremdschlüssel zu Abteilungen), Datum, ...
    
1. **Waffenerwerb:**
    - Attribute: ErwerbID (Primärschlüssel), MitgliederID (Fremdschlüssel zu Mitglieder), AbteilungsID (Fremdschlüssel zu Abteilungen), Datum, Erwerbsvoraussetzung erfüllt (Ja/Nein)