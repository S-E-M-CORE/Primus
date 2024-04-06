

/*
    Per Id des Members und einer GET function.
    Sollen alle Attribute wie z.B. Vorname,alter, Telefon, Poz, .... auf der Webseite angezeigt werden.
*/


displayMemberData();


async function displayMemberData() 
{
    try 
    {
        const memberId = 2; // Beispielhaft festgelegte Mitglieds-ID
        const apiClient = new PrimusApiClient(`http://localhost:8000`);

        const memberData = await apiClient.getMemberById(memberId);

        updateHTML(memberData);
    } catch (error) 
    {
        console.error('Fehler beim Abrufen der Mitgliedsdaten:', error);
        // Hier kannst du die Fehlerbehandlung ergänzen, z.B. eine Fehlermeldung auf der Seite anzeigen
    }
}
/*
Die Funktion ist dazu alle infomationen die von allen benötigten Jason Objekt kommen anzuzeigen. 

Parameters:
memberData - zeigen Vorname
adresseData - zeigen Postleitzahl, Wohnort, Straßename, Hausnummer

*/
function updateHTML(memberData , adresseData) 
{
    error_DB_Anomalie(memberData);     // wir überprüfen die Ressource die wir bekommen haben.

    let currentUser = memberData[0];    // 0 weil wir nur nach einem User Fragen wollen.
    
    JSON.stringify(memberData);
    document.getElementById('FirstName').textContent = `Vorname: ${currentUser.firstName}`;
    document.getElementById('LastName').textContent = `Nachname: ${currentUser.lastName}`;
    document.getElementById('date').textContent = `Geburtstag: ${currentUser.birthDate}`;
    document.getElementById('Member_email').textContent = `Email address: ${currentUser.email}`;
    document.getElementById('phoneNumber').textContent = `Telefonnummer: ${currentUser.phoneNumber}`;
    //document.getElementById('Poz').textContent = `Postleitzahl: ${currentUser.phoneNumber}`;
    
}
    
// check for single User.
function error_DB_Anomalie(memberData)
{
    if(memberData[1] !== undefined)
    {
        alert("Datenbank Anomalie erkannt. Mindestens 2 Nutzer mit ID currentUser.id");
    }
}

