
/*
    Per Id des Members und einer GET function.
    Sollen alle Attribute wie z.B. Vorname,alter, Telefon, Poz, .... auf der Webseite angezeigt werden.
*/

displayController();

async function displayController()
{
    let memberData = await displayMemberData();       // gibt uns das Adresse Jason Objekt.
   //let adresseData = displayAdresseData();     // gibt uns das Adresse Jason Objekt.

    adresseData = 1; // Damit es funktioniert muss auf Sascha warten. 

    updateHTML(memberData, adresseData);        // ändert den angezeigten Text.
}

async function displayMemberData() 
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const apiClient = new PrimusApiClient(`http://localhost:8000`);

        const memberData = await apiClient.getMemberById(memberId);
        JSON.stringify(memberData);
        return memberData;

    } 
    catch (error) 
    {
        console.error('Fehler beim Abrufen der Mitgliedsdaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    }
}

/*
*/ 
// async function displayAdresseData()
// {
// } 

/*
Die Funktion ist dazu alle infomationen die von allen benötigten Jason Objekten kommen  

Parameters:
    memberData - zeigen Vorname
    adresseData - zeigen Postleitzahl, Wohnort, Straßename, Hausnummer
*/
function updateHTML(memberData , adresseData) 
{
    error_DB_Anomalie(memberData, adresseData);     // wir überprüfen die Ressource die wir bekommen haben.

    let currentUserMember   = memberData[0];    // 0 weil wir nur nach einem User Fragen wollen.
    //let currentUserAdresse   = adresseData[0];   //
    
    // currentUserMember
    document.getElementById('FirstName').textContent = `Vorname: ${currentUserMember.firstName}`;
    document.getElementById('LastName').textContent = `Nachname: ${currentUserMember.lastName}`;
    document.getElementById('date').textContent = `Geburtstag: ${currentUserMember.birthDate}`;
    document.getElementById('Member_email').textContent = `Email address: ${currentUserMember.email}`;
    document.getElementById('phoneNumber').textContent = `Telefonnummer: ${currentUserMember.phoneNumber}`;
    
    //currentUserAdresse
    //document.getElementById('Poz').textContent = `Postleitzahl: ${currentUserAdresse.phoneNumber}`;
}
    
// check for single User.
function error_DB_Anomalie(memberData, adresseData)
{
    if(memberData[1] !== undefined)
    {
        alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    }

    // if(adresseData[1] !== undefined)
    // {
    //     alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    // }
}



