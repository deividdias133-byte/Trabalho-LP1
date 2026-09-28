#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Astronauta{
    
    private:
    
    string cpf;
    string nome;
    int idade;
    bool vivo;
    bool disponivel;

    public:
    Astronauta(string cpf, string nome, int idade){
        this-> cpf = cpf;
        this-> nome = nome;
        this-> idade = idade;
        this-> vivo = true;
        this-> disponivel = true;
    }
    
    string getcpf(){
        return cpf;
    }
    string getnome(){
        return nome;
    }
    int getidade(){
        return idade;
    }
    bool estavivo(){
        return vivo;
    }
    bool estadisponivel(){
        return disponivel;
    }
    void embarcar(){
        disponivel = false;
    }
    void desembarcar(){
        if (vivo == true){
            disponivel = true;
        }
    }
    void morrer(){
        vivo = false;
        disponivel = false;
    }


};

class Voo{
    private:
    int codigo;
    string estado;
    vector<string>cpfs;
    
    public:
    Voo(int codigo){
        this-> codigo = codigo;
        estado = "planejado";
    }
    int getcodigo(){
        return codigo;
    }
    string getestado(){
        return estado;
    }
int getQuantidadeAstronautas(){
    return cpfs.size();
}
string getcpf(int posicao){
    return cpfs[posicao];
}
bool temastronautas(string cpf) {
    for (int i = 0; i < cpfs.size(); i++){
        if(cpfs[i] == cpf) {
            return true;
        }
    }
    return false;
}
void adicionarastronauta(string cpf){
    cpfs.push_back(cpf);
}
bool removerastronauta(string cpf){
    for (int i = 0; i < cpfs.size(); i ++){
        if ( cpfs [i] == cpf) {
            cpfs.erase(cpfs.begin() + i);
            return true;
        }
    }
    return false;
}
void lancar(){
    estado = "em curso";
}
void explodir(){
    estado = "finalizado com explosao";
}
void finalizar(){
    estado = "finalizado com sucesso";
}
};

class Agencia{
    private:
    vector<Astronauta>astronautas;
    vector<Voo>voos;
    int buscarastronauta(string cpf){
        for (int i = 0; i < astronautas.size(); i ++){
            if (astronautas[i].getcpf() == cpf){
                return i;
            }
        }
        return -1;
    }
    int buscarvoo(int codigo){
        for (int i = 0; i < voos.size(); i ++){
            if (voos[i].getcodigo() == codigo){
                return i;
            }
        }
        return -1;
    }

    public:

    void cadastrarAstronauta(string cpf, string nome, int idade){
    if (buscarastronauta(cpf) != -1   ) {  
        cout << "ERRO: astronauta com CPF " << cpf << " ja cadastrado" << endl;
    } else {
        astronautas.push_back(Astronauta(cpf, nome, idade));
        cout << "OK: astronauta " << cpf << " cadastrado" << endl;
    }
}

    void cadastrarVoo(int codigo){
        if (buscarvoo(codigo) != -1){
            cout << "ERRO: voo " << codigo << " ja cadastrado" << endl;
    }
     else{
        voos.push_back(Voo(codigo));
        cout << "OK: voo " << codigo << " cadastrado" << endl;
    }
}

    void adicionarAstronauta(string cpf, int codigo){
        int posastro = buscarastronauta(cpf);
        int posvoo = buscarvoo(codigo);

        if (posastro == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        if (posvoo == -1){
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if(voos[posvoo].getestado() != "planejado"){
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if(!astronautas[posastro].estavivo()) {
            cout << "ERRO: astronauta " << cpf << " esta morto" << endl;
            return;
        }
        if(voos[posvoo].temastronautas(cpf)){
            cout << "ERRO: astronauta " << cpf << " ja esta no voo " << codigo << endl;
            return;
        }
        voos[posvoo].adicionarastronauta(cpf);
            cout << "OK: astronauta " << cpf << " adicionado ao voo " << codigo << endl;
        
    }

    void removerAstronauta(string cpf, int codigo){

        int posastro = buscarastronauta(cpf);
        int posvoo = buscarvoo(codigo);

          if (posastro == -1){
            cout << "ERRO: astronauta " << cpf << " nao cadastrado" << endl;
            return;
        }
        if (posvoo == -1){
            cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
            return;
        }
        if(voos[posvoo].getestado() != "planejado"){
            cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
            return;
        }
        if(!voos[posvoo].temastronautas(cpf)){
            cout << "ERRO: astronauta " << cpf << " nao esta no voo " << codigo << endl;
            return;
        }
        voos[posvoo].removerastronauta(cpf);
        cout << "OK: astronauta " << cpf << " removido do voo " << codigo << endl;
    }

    void lancarVoo(int codigo) {
    int posvoo = buscarvoo(codigo);

    if (posvoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }
    if (voos[posvoo].getestado() != "planejado") {
        cout << "ERRO: voo " << codigo << " nao esta planejado" << endl;
        return;
    }
    if (voos[posvoo].getQuantidadeAstronautas() == 0) {
        cout << "ERRO: voo " << codigo << " nao possui astronautas" << endl;
        return;
    }
    for (int i = 0; i < voos[posvoo].getQuantidadeAstronautas(); i++) {
        string cpfAtual = voos[posvoo].getcpf(i);
        int posAstroAtual = buscarastronauta(cpfAtual);

        if (!astronautas[posAstroAtual].estavivo()) {  
            cout << "ERRO: astronauta " << cpfAtual << " esta morto" << endl;
            return;
        }
        if (!astronautas[posAstroAtual].estadisponivel()) { 
            cout << "ERRO: astronauta " << cpfAtual << " esta indisponivel" << endl;
            return;
        }
    }

   
    for (int i = 0; i < voos[posvoo].getQuantidadeAstronautas(); i++) {
        string cpfAtual = voos[posvoo].getcpf(i);
        int posAstroAtual = buscarastronauta(cpfAtual);
        astronautas[posAstroAtual].embarcar();
    }

    voos[posvoo].lancar();
    cout << "OK: voo " << codigo << " lancado" << endl;
}

    void explodirVoo(int codigo) {
    int posvoo = buscarvoo(codigo);

    if (posvoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }
    if (voos[posvoo].getestado() != "em curso") {  
        cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
        return;
    }

    for (int i = 0; i < voos[posvoo].getQuantidadeAstronautas(); i++) {
        string cpfAtual = voos[posvoo].getcpf(i);
        int posAstroAtual = buscarastronauta(cpfAtual);
        astronautas[posAstroAtual].morrer();  
    }

    voos[posvoo].explodir();
    cout << "OK: voo " << codigo << " explodiu" << endl;
}

    void finalizarVoo(int codigo) {
    int posvoo = buscarvoo(codigo);

    if (posvoo == -1) {
        cout << "ERRO: voo " << codigo << " nao cadastrado" << endl;
        return;
    }
    if (voos[posvoo].getestado() != "em curso") {
        cout << "ERRO: voo " << codigo << " nao esta em curso" << endl;
        return;
    }

    for (int i = 0; i < voos[posvoo].getQuantidadeAstronautas(); i++) {
        string cpfAtual = voos[posvoo].getcpf(i);
        int posAstroAtual = buscarastronauta(cpfAtual);
        astronautas[posAstroAtual].desembarcar();  
    }

    voos[posvoo].finalizar();
    cout << "OK: voo " << codigo << " finalizado com sucesso" << endl;
    }

    void listarVoos() {
    cout << "LISTA DE VOOS" << endl;

    cout << "== planejado ==" << endl;
    bool achouPlanejado = false;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getestado() == "planejado") {
            achouPlanejado = true;
            cout << "Voo " << voos[i].getcodigo() << ": ";

            if (voos[i].getQuantidadeAstronautas() == 0) {
                cout << "sem astronautas" << endl;
            } else {
                for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                    string cpfAtual = voos[i].getcpf(j);
                    int posAstro = buscarastronauta(cpfAtual);
                    cout << cpfAtual << " " << astronautas[posAstro].getnome();
                    if (j < voos[i].getQuantidadeAstronautas() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
    }
    if (!achouPlanejado) {
        cout << "(nenhum)" << endl;
    }

           cout << "== em curso ==" << endl;
    bool achouEmCurso = false;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getestado() == "em curso") {
            achouEmCurso = true;
            cout << "Voo " << voos[i].getcodigo() << ": ";

            if (voos[i].getQuantidadeAstronautas() == 0) {
                cout << "sem astronautas" << endl;
            } else {
                for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                    string cpfAtual = voos[i].getcpf(j);
                    int posAstro = buscarastronauta(cpfAtual);
                    cout << cpfAtual << " " << astronautas[posAstro].getnome();
                    if (j < voos[i].getQuantidadeAstronautas() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
    }
    if (!achouEmCurso) {
        cout << "(nenhum)" << endl;
    }
    cout << "== finalizado com sucesso ==" << endl;
    bool achouSucesso = false;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getestado() == "finalizado com sucesso") {
            achouSucesso = true;
            cout << "Voo " << voos[i].getcodigo() << ": ";

            if (voos[i].getQuantidadeAstronautas() == 0) {
                cout << "sem astronautas" << endl;
            } else {
                for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                    string cpfAtual = voos[i].getcpf(j);
                    int posAstro = buscarastronauta(cpfAtual);
                    cout << cpfAtual << " " << astronautas[posAstro].getnome();
                    if (j < voos[i].getQuantidadeAstronautas() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
    }
    if (!achouSucesso) {
        cout << "(nenhum)" << endl;
    }
    
     cout << "== finalizado com explosao ==" << endl;
    bool achouExplosao = false;
    for (int i = 0; i < voos.size(); i++) {
        if (voos[i].getestado() == "finalizado com explosao") {
            achouExplosao = true;
            cout << "Voo " << voos[i].getcodigo() << ": ";

            if (voos[i].getQuantidadeAstronautas() == 0) {
                cout << "sem astronautas" << endl;
            } else {
                for (int j = 0; j < voos[i].getQuantidadeAstronautas(); j++) {
                    string cpfAtual = voos[i].getcpf(j);
                    int posAstro = buscarastronauta(cpfAtual);
                    cout << cpfAtual << " " << astronautas[posAstro].getnome();
                    if (j < voos[i].getQuantidadeAstronautas() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
    }
    if (!achouExplosao) {
        cout << "(nenhum)" << endl;
    }
    }
    void listarMortos(){
        cout << "ASTRONAUTAS MORTOS" << endl;
    bool achouMorto = false;

    for (int i = 0; i < astronautas.size(); i++) {
        if (astronautas[i].estavivo() == false) {
            achouMorto = true;
            cout << astronautas[i].getcpf() << " " << astronautas[i].getnome() << " - voos:";

            for (int j = 0; j < voos.size(); j++) {
                if (voos[j].getestado() != "planejado" && voos[j].temastronautas(astronautas[i].getcpf())) {
                    cout << " " << voos[j].getcodigo();
                }
            }
            cout << endl;
        }
    }

    if (!achouMorto) {
        cout << "(nenhum)" << endl;
    }
    }
    
};

int main() {
    Agencia agencia;
    string comando;

    while (cin >> comando) {   // le uma palavra; para no FIM ou quando a entrada acaba
        if (comando == "FIM") {
            break;
        } else if (comando == "CADASTRAR_ASTRONAUTA") {
            string cpf, nome;
            int idade;
            cin >> cpf >> idade;
            getline(cin >> ws, nome);   // o nome vem por ultimo e pode ter espacos
            agencia.cadastrarAstronauta(cpf, nome, idade);
        } else if (comando == "CADASTRAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.cadastrarVoo(codigo);
        } else if (comando == "ADICIONAR_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.adicionarAstronauta(cpf, codigo);
        } else if (comando == "REMOVER_ASTRONAUTA") {
            string cpf;
            int codigo;
            cin >> cpf >> codigo;
            agencia.removerAstronauta(cpf, codigo);
        } else if (comando == "LANCAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.lancarVoo(codigo);
        } else if (comando == "EXPLODIR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.explodirVoo(codigo);
        } else if (comando == "FINALIZAR_VOO") {
            int codigo;
            cin >> codigo;
            agencia.finalizarVoo(codigo);
        } else if (comando == "LISTAR_VOOS") {
           agencia.listarVoos();
        } else if (comando == "LISTAR_MORTOS") {
            agencia.listarMortos();
        } else {
            cout << "ERRO: comando desconhecido " << comando << endl;
        }
    }

    return 0;
}
