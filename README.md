# JARVIS - Assistente Vocale AI

JARVIS è un assistente vocale avanzato basato su C che integra riconoscimento vocale, risposte basate su AI e funzionalità text-to-speech. L'assistente risponde alle parole di attivazione "jarvis" o "darwin" e può eseguire vari compiti incluse richieste meteo, riproduzione musicale, gestione notifiche, controllo remoto SSH e conversazione generale con memoria persistente.

## Caratteristiche

- **Riconoscimento Vocale**: Riconoscimento vocale in tempo reale utilizzando l'API Vosk
- **Integrazione AI**: Alimentato dal modello Llama 4 Scout di Groq per risposte intelligenti
- **Text-to-Speech**: Sintesi vocale italiana utilizzando Google Text-to-Speech (gtts-cli)
- **Controllo Musicale**: Riproduzione automatica della musica locale e remota tramite SSH
- **Informazioni Meteo**: Richieste meteo per Bologna, Italia con visualizzazione ASCII art
- **Sistema Notifiche**: Gestione promemoria con invio via Telegram e notifiche desktop
- **Controllo Remoto SSH**: Comando di dispositivi remoti (laptop1)
- **Memoria Persistente**: Sistema di memoria a lungo termine per apprendimento continuo
- **Risposte JSON**: Formato di risposta strutturato per azioni precise

## Prerequisiti

### Librerie Richieste
- **Vosk**: Libreria di riconoscimento vocale (vosk_api.h + libvosk.so)
- **Jansson**: Libreria di parsing JSON
- **gtts-cli**: Google Text-to-Speech CLI per sintesi vocale italiana
- **mpv**: Lettore multimediale per audio e musica
- **jq**: Processore JSON per gestione cronologia conversazioni
- **curl**: Client HTTP per chiamate API e notifiche Telegram
- **notify-send**: Sistema notifiche desktop Linux
- **ssh**: Client SSH per controllo remoto

### Requisiti di Sistema
- Sistema operativo basato su Linux
- Microfono per input audio
- Dispositivo di output audio
- Connessione internet per chiamate API AI

## Installazione

### 1. Installare le Dipendenze

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install curl mpv jq libnotify-bin openssh-client build-essential
pip3 install gTTS-cli
```

**Per Vosk:**
- Scarica l'API C di Vosk da [https://alphacephei.com/vosk/](https://alphacephei.com/vosk/)
- Hai bisogno di questi file specifici:
  - `vosk_api.h` (file header)
  - `libvosk.so` (libreria condivisa)
- Scarica il modello italiano `vosk-model-it-0.22`
- Estrai il modello nella directory del progetto
- Posiziona `vosk_api.h` e `libvosk.so` nella directory del progetto

**Per Jansson:**
```bash
sudo apt install libjansson-dev
```

### 2. Configurazione API e Credenziali
**Groq API:**
Sostituisci il token nell'header Authorization del comando curl nel codice:
```bash
-H "Authorization: Bearer LA_TUA_CHIAVE_API_GROQ"
```

**Telegram Bot (per notifiche):**
Configura il token del bot e chat ID nel codice:
```c
// Sostituisci TOKEN e CHATID con i tuoi valori
"https://api.telegram.org/botTOKEN-d chat_id=CHATID"
```

**SSH (per controllo remoto):**
Configura l'accesso SSH senza password:
```bash
ssh-keygen -t rsa
ssh-copy-id gioele@192.168.1.113
```

### 3. Compilazione
```bash
export LD_LIBRARY_PATH=~/vosk
gcc test.c -o test -I. -L. -lvosk -ljansson
```

## Utilizzo

### Esecuzione dell'Assistente
```bash
export LD_LIBRARY_PATH=~/vosk
arecord -f S16_LE -r 16000 -c 1 | ./test
```

### Comandi Vocali
- **Parole di Attivazione**: Dì "jarvis" o "darwin" nella frase per attivare l'assistente
- **Meteo**: Chiedi le condizioni meteo a Bologna con visualizzazione ASCII art
- **Musica Locale**: Richiedi la riproduzione musicale con "metti musica"
- **Musica Remota**: Richiedi musica su laptop1 con "metti musica su laptop1"
- **Notifiche**: "Ricordami di [cosa] tra [tempo]" per impostare promemoria
- **Spegnimento Locale**: "spegniti" per terminare l'assistente
- **Spegnimento Remoto**: "spegni laptop1" per spegnere il dispositivo remoto
- **Richieste Generali**: Fai qualsiasi domanda per risposte basate su AI

## Configurazione

### Prompt di Sistema
L'assistente è configurato con una personalità e comportamenti specifici:
- **Nome**: JARVIS (risponde anche a "darwin")
- **Proprietario**: Gioele (15 anni, studente ITIS informatica a Bologna)
- **Lingua**: Italiano
- **Formato Risposta**: JSON strutturato con campi "risposta" e "azione"
- **Memoria Persistente**: Salvataggio automatico di informazioni importanti
- **Contesto Personale**: Conosce interessi (Spider-Man, Iron Man, Roblox, Netflix)
- **Comandi Speciali**: Gestione musica, notifiche, controllo remoto SSH

### Impostazioni Audio
- **Frequenza di Campionamento**: 16kHz
- **Formato**: 16-bit Little Endian
- **Canali**: Mono
- **Text-to-Speech**: Google TTS italiano via gtts-cli
- **Riproduzione**: mpv per audio e musica

## Struttura File
```
progetto/
├── test.c              # Codice sorgente principale
├── test                # Eseguibile compilato
├── vosk_api.h          # File header Vosk
├── libvosk.so          # Libreria condivisa Vosk
├── vosk-model-it-0.22/ # Modello riconoscimento vocale italiano
├── history.json        # Cronologia conversazioni (formato JSON)
├── output.txt          # Risposta AI completa
├── risposta.txt        # Testo di risposta estratto
├── azione.txt          # Comando azione estratto
├── memoria.txt         # Memoria persistente a lungo termine
├── meteo.txt           # Dati meteo temporanei
├── date.txt            # Timestamp corrente
├── notify.txt          # Dati notifiche temporanei
├── voce.mp3            # File audio TTS temporaneo
└── ~/Downloads/musica/ # Directory musica (file *.mp3)
```

## Come Funziona

1. **Inizializzazione Sistema**: Carica meteo, orario, data e memoria persistente
2. **Cattura Audio**: Il programma cattura l'audio dal microfono usando `arecord`
3. **Riconoscimento Vocale**: Vosk elabora lo stream audio e converte il parlato in testo
4. **Rilevamento Parole di Attivazione**: Monitora "jarvis" o "darwin" nel testo riconosciuto
5. **Costruzione Cronologia**: Aggiunge il messaggio utente alla cronologia JSON conversazione
6. **Elaborazione AI**: Invia cronologia completa all'API Groq con prompt di sistema
7. **Parsing Risposta**: Estrae risposta testuale e comando azione dal JSON ricevuto
8. **Text-to-Speech**: Converte la risposta in parlato usando Google TTS
9. **Esecuzione Azioni**: Elabora comandi speciali (musica, notifiche, SSH, memoria)
10. **Salvataggio Cronologia**: Aggiunge risposta AI alla cronologia per contesto futuro

## Comandi Speciali

### Riproduzione Musicale
Quando la risposta AI contiene `{musica:avvio}`, il sistema riproduce automaticamente i file musicali da `~/Downloads/musica/`

### Spegnimento Sistema
Quando la risposta AI contiene `{spegnimento:avvio}`, l'assistente si termina

### Richieste Meteo
Le informazioni meteo vengono recuperate da `wttr.in/Bologna` con formattazione personalizzata

## Integrazione API

## Integrazione API

L'assistente utilizza l'API di Groq con la seguente configurazione:
- **Modello**: meta-llama/llama-4-scout-17b-16e-instruct
- **Endpoint**: https://api.groq.com/openai/v1/chat/completions
- **Content-Type**: application/json
- **Autenticazione**: Token Bearer richiesto
- **Cronologia**: Invia l'intera cronologia conversazione per contesto

### Servizi Esterni
- **wttr.in**: Servizio meteo per Bologna
- **Telegram Bot API**: Invio notifiche remote
- **Google TTS**: Sintesi vocale italiana

## Risoluzione Problemi

### Problemi Comuni
1. **Audio Input**: Controlla permessi microfono e configurazione ALSA
2. **Modello Vosk Non Trovato**: Verifica il modello italiano nella directory corretta
3. **API Authentication**: Controlla validità chiave API Groq
4. **Dipendenze Librerie**: Installa tutte le librerie richieste
5. **SSH Non Funziona**: Configura chiavi SSH senza password
6. **Telegram Non Invia**: Verifica token bot e chat ID
7. **JSON Malformato**: L'AI deve rispondere solo in JSON valido
8. **gtts-cli Non Trovato**: Installa con `pip3 install gTTS-cli`
9. **Memoria Non Salvata**: Verifica permessi scrittura file `memoria.txt`
10. **Notifiche Non Mostrate**: Installa `libnotify-bin`

### Debug Mode
Il programma mostra informazioni di debug:
- Timestamp corrente e data
- Condizioni meteo Bologna
- Prompt di sistema completo
- Cronologia conversazioni JSON
- Testo riconosciuto da Vosk
- Comando curl completo per API
- Risposta AI grezza
- Azione estratta e parametri
- Comandi sistema eseguiti

## Personalizzazione

### Cambio Proprietario
Modifica le informazioni personali nel codice:
```c
char abitudini[] = "... Mi chiamo [NOME], ho [ETA] anni ...";
```

### Aggiunta Nuove Azioni
1. Aggiungi nuovo case nel parsing azioni:
```c
if (strstr(azionetesto, "nuova_azione")) {
    // Esegui comando
}
```
2. Aggiorna prompt di sistema con nuova azione valida

### Configurazione SSH
Modifica indirizzo IP del dispositivo remoto:
```c
"ssh gioele@[IP_ADDRESS]"
```

## Licenza

Questo progetto è per uso educativo e personale. Per favore rispetta i termini di servizio di tutte le API e librerie integrate.

## Personalizzazione Lingua

### Passaggio alla Versione Inglese

Se vuoi passare alla versione inglese, puoi fare questo:

1. **Cambia il modello Vosk**: Sostituisci il modello italiano con uno inglese nella directory del progetto
   - Scarica un modello inglese come `vosk-model-en-us-0.22` da [Modelli Vosk](https://alphacephei.com/vosk/models.html)
   - Aggiorna il percorso del modello nel codice:
   ```c
   VoskModel *model = vosk_model_new("vosk-model-en-us-0.22");
   ```

2. **Sostituisci il prompt di sistema**: Modifica la variabile prompt per usare istruzioni inglesi
   - Cambia le istruzioni italiane con equivalenti inglesi
   - Aggiorna la località meteo se necessario (sostituisci Bologna con la tua città)

3. **Sostituisci text-to-speech con modalità inglese**: Aggiorna le impostazioni voce eSpeak
   - Cambia dalla voce italiana `it+f3` alla voce inglese come `en+f3`
   - Aggiorna sia nella funzione `speak()` che nel comando curl:
   ```c
   "espeak -v en+f3 -s 110"
   ```

## Crediti

- **Vosk**: Riconoscimento vocale
- **Groq**: Modello linguistico AI
- **eSpeak**: Sintesi text-to-speech
- **Jansson**: Parsing JSON
