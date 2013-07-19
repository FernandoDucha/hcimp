/* 
 * File:   NumberPartitionProblem_MPZ.cpp
 * Author: fernando
 * 
 * Created on 29 de Agosto de 2011, 10:59
 */

#include "NumberPartitionProblem_MPZ.h"
NumberPartitionProblem_MPZ::NumberPartitionProblem_MPZ(char * problemFile) {
    soma = 0;
    //cout<<2<<endl;
    lerArquivo(problemFile);
    //cout<<3<<endl;
    this->problemFile = problemFile;
    for (int i = 0; i < nroParticoes; i++) {
        partitionsSums[i] = 0;
    }
    // CompleteKarmarkarKarp k(numberSource, nroParticoes);
    // bestPartitions = new ListStructure<number_element_MPZ>*[nroParticoes];
    //    for (int i = 0; i < nroParticoes; i++) {
    //        bestPartitions[i] = NULL;
    //    }
    maxPertubations = quantidade / 1.5;
    pertubations = new Pertubation[maxPertubations];
    constructPertubations();
}

void NumberPartitionProblem_MPZ::lerArquivo(char * problemFile) {
    //cout<<4<<endl;
    ifstream filestr;
    char buff[10000];
    for (int i = 0; i < 100; i++)
        buff[i] = '\0';
    filestr.open(problemFile);
    filestr >> tempo; // = atoi(buff);

    //filestr.getline(buff, 100);
    filestr >> buff;

    //filestr.getline(buff, 100);
    filestr >> quantidade; // = atoi(buff);
    numberSource = new ListStructure<number_element_mpz > (ListStructure<number_element_mpz>::ORDEM_DECRESCENTE);
    filestr >> buff;
    filestr >> nroParticoes;
    partitionsSums = new mpz_class[nroParticoes];
    partitions = new ListStructure<number_element_mpz>*[nroParticoes];
    bestPartitions = new ListStructure<number_element_mpz>*[nroParticoes];
    for (int i = 0; i < nroParticoes; i++) {
        partitionsSums[i] = 0;
        partitions[i] = new ListStructure<number_element_mpz > (ListStructure<number_element_mpz>::ORDEM_DECRESCENTE);
        bestPartitions[i] = new ListStructure<number_element_mpz > (ListStructure<number_element_mpz>::ORDEM_DECRESCENTE);
    }
    filestr >> buff;

    for (int i = 0; i < quantidade; i++) {
        mpz_class temp = 0;
        filestr >> temp;
        number_element_mpz novo(temp);
        numberSource->Add(novo);
        soma += novo.id;
        //cout<<novo.id<<endl;
    }
    //numberSource->PrintLista();
    media = soma / nroParticoes;
    if ((soma % 2) == 1) {
        media += 1;
    }
    //numberSource->PrintLista();
    filestr.close();
}
//nao usa o movimento de movimentoRealocaMaiorDiferenca()

void NumberPartitionProblem_MPZ::generateInitialSolEqualDivision() {
    int i = 0;
    clearPartitions();
    node_list_struct<number_element_mpz> * number = numberSource->nextFromLastAcc();
    while (number != NULL) {
        number_element_mpz n(number->element.id);
        int k = i % nroParticoes;
        partitions[k]->Add(n);
        partitionsSums[k] += n.id;
        i++;
        number = numberSource->nextFromLastAcc();
    }
    resultado = calculaResultado();
    // while(movimentoRealocaMaiorDiferenca());
    //cout << resultado << endl;
}
//usa o movimento de movimentoRealocaMaiorDiferenca()

void NumberPartitionProblem_MPZ::generateInitialSolEqualDivisionComRealoc() {
    int i = 0;
    clearPartitions();
    node_list_struct<number_element_mpz> * number = numberSource->nextFromLastAcc();
    while (number != NULL) {
        mpz_class n = number->element.id;
        int k = i % nroParticoes;
        partitions[k]->Add(number->element);
        partitionsSums[k] += n;
        i++;
        number = numberSource->nextFromLastAcc();
    }
    resultado = calculaResultado();
    while (movimentoRealocaMaiorDiferenca());
    // cout << resultado << endl;
}

mpz_class NumberPartitionProblem_MPZ::achaMelhorTroca(int & conjuntoA, number_element_mpz & numeroA, int & conjuntoB, number_element_mpz & numeroB) {
    //Trocas
    mpz_class resultadoTroca = resultado;
    for (int i = 0; i < nroParticoes; i++) {
        for (int j = i + 1; j < nroParticoes; j++) {
            node_list_struct<number_element_mpz> * lastAccI;
            while ((lastAccI = partitions[i]->nextFromLastAcc()) != NULL) {
                node_list_struct<number_element_mpz>*lastAccJ;
                while (((lastAccJ = partitions[j]->nextFromLastAcc()) != NULL)) {
                    partitionsSums[i] = partitionsSums[i] - lastAccI->element.id + lastAccJ->element.id;
                    partitionsSums[j] = partitionsSums[j] - lastAccJ->element.id + lastAccI->element.id;
                    mpz_class tempRes = calculaResultado();
                    if (tempRes < resultadoTroca) {
                        conjuntoA = i;
                        numeroA = lastAccI->element;
                        conjuntoB = j;
                        numeroB = lastAccJ->element;
                        resultadoTroca = tempRes;
                    }
                    partitionsSums[j] = partitionsSums[j] - lastAccI->element.id + lastAccJ->element.id;
                    partitionsSums[i] = partitionsSums[i] - lastAccJ->element.id + lastAccI->element.id;
                }
            }
        }
    }
    return resultadoTroca;
}

mpz_class NumberPartitionProblem_MPZ::achaMelhorRealocacao(int & conjuntoA, number_element_mpz & numeroA, int &conjuntoB) {
    mpz_class resultadoRealoc = resultado;
    for (int i = 0; i < nroParticoes; i++) {
        for (int j = i + 1; j < nroParticoes; j++) {
            node_list_struct<number_element_mpz> * lastAccI;
            while ((lastAccI = partitions[i]->nextFromLastAcc()) != NULL) {
                partitionsSums[i] = partitionsSums[i] - lastAccI->element.id;
                partitionsSums[j] = partitionsSums[j] + lastAccI->element.id;
                mpz_class tempRes = calculaResultado();
                // cout<<lastAccI->id<<"--"<<tempRes<<endl;
                if (tempRes < resultadoRealoc) {
                    conjuntoA = i;
                    numeroA = lastAccI->element;
                    conjuntoB = j;
                    resultadoRealoc = tempRes;
                }
                partitionsSums[j] = partitionsSums[j] - lastAccI->element.id;
                partitionsSums[i] = partitionsSums[i] + lastAccI->element.id;

            }
        }
    }
    return resultadoRealoc;
}

mpz_class NumberPartitionProblem_MPZ::primeiraMelhorTroca(int & conjuntoA, number_element_mpz & numeroA, int & conjuntoB, number_element_mpz & numeroB) {
    mpz_class resultadoTroca = resultado;
    for (int i = 0; i < nroParticoes; i++) {
        for (int j = i + 1; j < nroParticoes; j++) {
            node_list_struct<number_element_mpz> * lastAccI;
            while ((lastAccI = partitions[i]->nextFromLastAcc()) != NULL) {
                node_list_struct<number_element_mpz>*lastAccJ;
                while (((lastAccJ = partitions[j]->nextFromLastAcc()) != NULL)) {
                    partitionsSums[i] = partitionsSums[i] - lastAccI->element.id + lastAccJ->element.id;
                    partitionsSums[j] = partitionsSums[j] - lastAccJ->element.id + lastAccI->element.id;
                    mpz_class tempRes = calculaResultado();
                    if (tempRes < resultadoTroca) {
                        conjuntoA = i;
                        numeroA = lastAccI->element;
                        conjuntoB = j;
                        numeroB = lastAccJ->element;
                        resultadoTroca = tempRes;
                        return resultadoTroca;
                    }
                    partitionsSums[j] = partitionsSums[j] - lastAccI->element.id + lastAccJ->element.id;
                    partitionsSums[i] = partitionsSums[i] - lastAccJ->element.id + lastAccI->element.id;
                }
            }
        }
    }
    return resultadoTroca;
}

mpz_class NumberPartitionProblem_MPZ::primeiraMelhorRealocacao(int & conjuntoA, number_element_mpz & numeroA, int &conjuntoB) {
    mpz_class resultadoRealoc = resultado;
    for (int i = 0; i < nroParticoes; i++) {
        for (int j = i + 1; j < nroParticoes; j++) {
            node_list_struct<number_element_mpz> * lastAccI;
            while ((lastAccI = partitions[i]->nextFromLastAcc()) != NULL) {
                partitionsSums[i] = partitionsSums[i] - lastAccI->element.id;
                partitionsSums[j] = partitionsSums[j] + lastAccI->element.id;
                mpz_class tempRes = calculaResultado();
                // cout<<lastAccI->id<<"--"<<tempRes<<endl;
                if (tempRes < resultadoRealoc) {
                    conjuntoA = i;
                    numeroA = lastAccI->element;
                    conjuntoB = j;
                    resultadoRealoc = tempRes;
                    return resultadoRealoc;
                }
                partitionsSums[j] = partitionsSums[j] - lastAccI->element.id;
                partitionsSums[i] = partitionsSums[i] + lastAccI->element.id;
            }
        }
    }
    return resultadoRealoc;
}

mpz_class NumberPartitionProblem_MPZ::escolheMelhorVizinho() {
    int conjuntoTrocaOrigem = 0;
    number_element_mpz numeroTrocaOrigem;
    int conjuntoTrocaDestino = 0;
    number_element_mpz numeroTrocaDestino;
    mpz_class resultadoTroca = achaMelhorTroca(conjuntoTrocaOrigem, numeroTrocaOrigem, conjuntoTrocaDestino, numeroTrocaDestino);
    int conjuntoRealocOrigem = 0;
    number_element_mpz numeroRealocOrigem;
    int conjuntoRealocDestino = 0;
    mpz_class resultadoRealoca = achaMelhorRealocacao(conjuntoRealocOrigem, numeroRealocOrigem, conjuntoRealocDestino);
    //    cout<<resultadoRealoca<<"--"<<resultadoTroca<<endl;
    if (resultadoTroca < resultadoRealoca) {
        partitions[conjuntoTrocaOrigem]->RemoveObject(numeroTrocaOrigem);
        partitions[conjuntoTrocaOrigem]->Add(numeroTrocaDestino);
        partitions[conjuntoTrocaDestino]->RemoveObject(numeroTrocaDestino);
        partitions[conjuntoTrocaDestino]->Add(numeroTrocaOrigem);
        partitionsSums[conjuntoTrocaOrigem] = partitionsSums[conjuntoTrocaOrigem] - numeroTrocaOrigem.id + numeroTrocaDestino.id;
        partitionsSums[conjuntoTrocaDestino] = partitionsSums[conjuntoTrocaDestino] - numeroTrocaDestino.id + numeroTrocaOrigem.id;
        // cout<<resultadoTroca<<" "<<calculaResultado()<<" "<<checkSolution()<<endl;
        return resultadoTroca;
    } else if (numeroRealocOrigem.id > 0) {
        partitions[conjuntoRealocOrigem]->RemoveObject(numeroRealocOrigem);
        partitions[conjuntoRealocDestino]->Add(numeroRealocOrigem);
        partitionsSums[conjuntoRealocOrigem] = partitionsSums[conjuntoRealocOrigem] - numeroRealocOrigem.id;
        partitionsSums[conjuntoRealocDestino] = partitionsSums[conjuntoRealocDestino] + numeroRealocOrigem.id;
        return resultadoRealoca;
    } else {
        return resultadoTroca;
    }
}

mpz_class NumberPartitionProblem_MPZ::escolhePrimeiroMelhorVizinho() {
    int conjuntoTrocaOrigem = 0;
    number_element_mpz numeroTrocaOrigem;
    int conjuntoTrocaDestino = 0;
    number_element_mpz numeroTrocaDestino;
    mpz_class resultadoTroca = primeiraMelhorTroca(conjuntoTrocaOrigem, numeroTrocaOrigem, conjuntoTrocaDestino, numeroTrocaDestino);
    int conjuntoRealocOrigem = 0;
    number_element_mpz numeroRealocOrigem;
    int conjuntoRealocDestino = 0;
    mpz_class resultadoRealoca = primeiraMelhorRealocacao(conjuntoRealocOrigem, numeroRealocOrigem, conjuntoRealocDestino);
    //    cout<<resultadoRealoca<<"--"<<resultadoTroca<<endl;
    if (resultadoTroca < resultadoRealoca) {
        partitions[conjuntoTrocaOrigem]->RemoveObject(numeroTrocaOrigem);
        partitions[conjuntoTrocaOrigem]->Add(numeroTrocaDestino);
        partitions[conjuntoTrocaDestino]->RemoveObject(numeroTrocaDestino);
        partitions[conjuntoTrocaDestino]->Add(numeroTrocaOrigem);
        partitionsSums[conjuntoTrocaOrigem] = partitionsSums[conjuntoTrocaOrigem] - numeroTrocaOrigem.id + numeroTrocaDestino.id;
        partitionsSums[conjuntoTrocaDestino] = partitionsSums[conjuntoTrocaDestino] - numeroTrocaDestino.id + numeroTrocaOrigem.id;
        return resultadoTroca;
    } else {
        partitions[conjuntoRealocOrigem]->RemoveObject(numeroRealocOrigem);
        partitions[conjuntoRealocDestino]->Add(numeroRealocOrigem);
        partitionsSums[conjuntoRealocOrigem] = partitionsSums[conjuntoRealocOrigem] - numeroRealocOrigem.id;
        partitionsSums[conjuntoRealocDestino] = partitionsSums[conjuntoRealocDestino] + numeroRealocOrigem.id;
        return resultadoRealoca;
    }
}

void NumberPartitionProblem_MPZ::firstImproved() {
    mpz_class resultadoAtual = 0;
    while ((resultadoAtual = escolhePrimeiroMelhorVizinho()) < resultado) {
        resultado = resultadoAtual;
    }
    // cout << resultado << endl;
}

void NumberPartitionProblem_MPZ::descida() {
    mpz_class resultadoAtual = 0;
    while ((resultadoAtual = escolheMelhorVizinho()) < resultado) {
        resultado = resultadoAtual;
    }
    //cout << resultado << endl;
}

void NumberPartitionProblem_MPZ::multiStart(int iter) {
    srand(time(NULL));
    generateInitialSolAleatorio();
    mpz_class melhorResultado = resultado;
    for (int i = 0; i < iter; i++) {
        descida();
        if (resultado < melhorResultado) {
            cout << resultado << "---" << melhorResultado << endl;
            bestResultado = melhorResultado = resultado;
            cloneSolutionToBest();
            if ((bestResultado == 1) || (bestResultado == 0)) {
                break;
            }
        }

        generateInitialSolAleatorio();
    }

}

mpz_class NumberPartitionProblem_MPZ::checkBestSolution() {
    mpz_class * partsum = new mpz_class[nroParticoes];
    for (int i = 0; i < nroParticoes; i++) {
        partsum[i] = 0;
        node_list_struct<number_element_mpz> * number = bestPartitions[i]->nextFromLastAcc();
        while (number != NULL) {
            partsum[i] += number->element.id;
            number = bestPartitions[i]->nextFromLastAcc();
        }
    }
    int min = 0;
    int max = 1;
    if (partsum[min] > partsum[max]) {
        min = 1;
        max = 0;
    }
    for (int i = 2; i < nroParticoes; i++) {
        if (partsum[i] > partsum[max]) {
            max = i;
        } else if (partsum[min] < partsum[i]) {
            min = i;
        }
    }
    mpz_class res = partsum[max] - partsum[min];
    delete [] partsum;
    return res;
}

mpz_class NumberPartitionProblem_MPZ::checkSolution() {
    mpz_class * partsum = new mpz_class[nroParticoes];
    for (int i = 0; i < nroParticoes; i++) {
        partsum[i] = 0;
        const node_list_struct<number_element_mpz> * number = partitions[i]->nextFromLastAcc();
        while (number != NULL) {
            partsum[i] += number->element.id;
            number = partitions[i]->nextFromLastAcc();
        }
    }
    int min = 0;
    int max = 1;
    if (partsum[min] > partsum[max]) {
        min = 1;
        max = 0;
    }
    for (int i = 2; i < nroParticoes; i++) {
        if (partsum[i] > partsum[max]) {
            max = i;
        } else if (partsum[min] < partsum[i]) {
            min = i;
        }
    }
    mpz_class res = partsum[max] - partsum[min];
    delete [] partsum;
    return res;
}

mpz_class NumberPartitionProblem_MPZ::getBestResultado() const {
    return bestResultado;
}

ListStructure<number_element_mpz>* NumberPartitionProblem_MPZ::getNumberSource() const {
    return numberSource;
}

int NumberPartitionProblem_MPZ::getNroParticoes() const {
    return nroParticoes;
}

void NumberPartitionProblem_MPZ::generateInitialSolGuloso() {
    clearPartitions();
    node_list_struct<number_element_mpz> * number = numberSource->nextFromLastAcc();
    while (number != NULL) {
        mpz_class n = number->element.id;
        int menor = menorParticao();
        number_element_mpz novo(n);
        partitions[menor]->Add(novo);
        partitionsSums[menor] += n;
        number = numberSource->nextFromLastAcc();
    }
    resultado = calculaResultado();
    //  movimentoRealocaMaiorDiferenca();
    int maior = maiorParticao();
    int menor = menorParticao();
    // cout << resultado << endl;
}

void NumberPartitionProblem_MPZ::generateInitialSolAleatorio() {
    clearPartitions();
    ListStructure<number_element_mpz> * cloneSource = numberSource->clone();
    do {
        number_element_mpz actualNumber = cloneSource->RemoveObject(cloneSource->retrieve_K_esimo(rand() % cloneSource->getSize())->element);
        int actualPart = rand() % nroParticoes;
        partitions[actualPart]->Add(actualNumber);
        partitionsSums[actualPart] += actualNumber.id;
    } while (cloneSource->getSize() > 0);
    resultado = calculaResultado();
    delete cloneSource;
}

void NumberPartitionProblem_MPZ::descidaAleatoria() {
    srand(time(NULL));
    int maxIter = 1000 * calculateMaxIter();
    int actualIter = 0;
    bool hitSrand = false;
    while (actualIter < maxIter) {
        bool melhorou = false;
        if (rand() % 2) {
            melhorou = movimentoTrocaAleatorio();
        } else {
            melhorou = movimentoRealocaAleatorio();
        }
        if (melhorou) {
            actualIter = 0;
            hitSrand = true;
        } else if (actualIter % (maxIter / 4) == 0) {
            srand(time(NULL));
        }

        actualIter++;
    }
    // cout << resultado << endl;
}

int NumberPartitionProblem_MPZ::calculateMaxIter() {
    int multi = 0;
    int summing = 0;
    for (int i = 0; i < nroParticoes; i++) {
        int sum = 0;
        for (int j = i + 1; j < nroParticoes; j++) {
            sum += partitions[j]->getSize();
        }
        multi += partitions[i]->getSize() * sum;
        summing += sum;
    }
    return multi + summing;
}

mpz_class NumberPartitionProblem_MPZ::getResultado() const {
    return resultado;
}
//troca dois elementos entre os dois conjuntos.

bool NumberPartitionProblem_MPZ::movimentoTrocaAleatorio() {
    int particaoA = rand() % nroParticoes;
    int particaoB;
    do {
        particaoB = rand() % nroParticoes;
    } while (particaoA == particaoB);
    number_element_mpz numeroA = this->partitions[particaoA]->retrieve_K_esimo(rand() % this->partitions[particaoA]->getSize())->element;
    number_element_mpz numeroB = this->partitions[particaoB]->retrieve_K_esimo(rand() % this->partitions[particaoB]->getSize())->element;
    if (avaliaTroca(numeroA.id, particaoA, numeroB.id, particaoB)) {
        partitions[particaoA]->RemoveObject(numeroA);
        partitions[particaoA]->Add(numeroB);
        partitions[particaoB]->RemoveObject(numeroB);
        partitions[particaoB]->Add(numeroA);
        return true;
    } else {
        return false;
    }
}
//retorna true se melhora.

bool NumberPartitionProblem_MPZ::avaliaTroca(mpz_class a, int conjuntoA, mpz_class b, int conjuntoB) {
    partitionsSums[conjuntoA] = partitionsSums[conjuntoA] - a + b;
    partitionsSums[conjuntoB] = partitionsSums[conjuntoB] - b + a;
    mpz_class difsum = calculaResultado();
    if (difsum < resultado) {
        resultado = difsum;
        return true;
    } else {
        partitionsSums[conjuntoA] = partitionsSums[conjuntoA] - b + a;
        partitionsSums[conjuntoB] = partitionsSums[conjuntoB] - a + b;
        return false;
    }
}

bool NumberPartitionProblem_MPZ::movimentoRealocaAleatorio() {
    int particaoA = rand() % nroParticoes;
    int particaoB;
    do {
        particaoB = rand() % nroParticoes;
    } while (particaoA == particaoB);
    number_element_mpz numeroA = this->partitions[particaoA]->retrieve_K_esimo(rand() % this->partitions[particaoA]->getSize())->element;
    partitionsSums[particaoA] = partitionsSums[particaoA] - numeroA.id;
    partitionsSums[particaoB] = partitionsSums[particaoB] + numeroA.id;
    mpz_class difsum = calculaResultado();
    if (difsum < resultado) {
        partitions[particaoA]->RemoveObject(numeroA);
        partitions[particaoB]->Add(numeroA);
        resultado = difsum;
        return true;
    } else {
        partitionsSums[particaoA] = partitionsSums[particaoA] + numeroA.id;
        partitionsSums[particaoB] = partitionsSums[particaoB] - numeroA.id;
        return false;
    }
}

bool NumberPartitionProblem_MPZ::movimentoRealocaMaiorDiferenca() {
    int biggerPart = maiorParticao();
    mpz_class diff = partitionsSums[biggerPart] - media;
    number_element_mpz closest = partitions[biggerPart]->retrieveClosest(number_element_mpz(diff));
    partitionsSums[biggerPart] -= closest.id;
    int smallerPart = menorParticao();
    partitionsSums[smallerPart] += closest.id;
    mpz_class tempRes = calculaResultado();
    if (tempRes < resultado) {
        resultado = tempRes;
        partitions[biggerPart]->RemoveObject(closest);
        partitions[smallerPart]->Add(closest);
        return true;
    } else {
        partitionsSums[biggerPart] += closest.id;
        partitionsSums[smallerPart] -= closest.id;
        return false;
    }
}

int NumberPartitionProblem_MPZ::maiorParticao() {
    int ret = 0;
    for (int i = 1; i < nroParticoes; i++) {
        if (partitionsSums[ret] < partitionsSums[i]) {
            ret = i;
        }
    }
    return ret;
}

int NumberPartitionProblem_MPZ::menorParticao() {
    int ret = 0;
    for (int i = 1; i < nroParticoes; i++) {
        if (partitionsSums[ret] > partitionsSums[i]) {
            ret = i;
        }
    }
    return ret;
}

mpz_class NumberPartitionProblem_MPZ::calculaResultado() {
    //    int sum=0;
    //    for(int i=0;i<nroParticoes;i++){
    //        for(int j=i+1;j<nroParticoes;j++){
    //            sum+=abs(partitionsSums[i]-partitionsSums[j]);
    //        }
    //    }
    //    int maiorPart=maiorParticao();
    //    sum=partitionsSums[maiorPart]-media;
    return partitionsSums[maiorParticao()] - partitionsSums[menorParticao()];
}

void NumberPartitionProblem_MPZ::clearPartitions() {
    for (int i = 0; i < nroParticoes; i++) {
        partitions[i]->ClearList();
        partitionsSums[i] = 0;
    }
}

NumberPartitionProblem_MPZ::~NumberPartitionProblem_MPZ() {
    delete numberSource;
    for (int i = 0; i<this->nroParticoes; i++) {
        delete partitions[i];
        delete bestPartitions[i];
    }
    delete [] bestPartitions;
    delete [] partitions;
    delete [] partitionsSums;
    delete [] pertubations;
}

void NumberPartitionProblem_MPZ::graspConstruction(float alpha) {
    clearPartitions();
    ListStructure<number_element_mpz> * numberSourceClone = numberSource->clone();
    while (numberSourceClone->getSize() > 0) {
        ListStructure<graspPair_MPZ> * GraspPairs = new ListStructure<graspPair_MPZ > (ListStructure<graspPair_MPZ>::ORDEM_CRESCENTE);
        node_list_struct<number_element_mpz> * number = numberSourceClone->nextFromLastAcc();
        int m = menorParticao();
        while (number != NULL) {
            partitionsSums[m] += number->element.id;
            mpz_class res = calculaResultado();
            graspPair_MPZ gp(res, number->element.id);
            GraspPairs->Add(gp);
            partitionsSums[m] -= number->element.id;
            number = numberSourceClone->nextFromLastAcc();
        }
        mpz_class diff = alpha * (GraspPairs->peekLast().id - GraspPairs->peekFirst().id);
        mpz_class RclLimit = GraspPairs->peekFirst().id + diff;
        ListStructure<graspPair_MPZ>* RCL = new ListStructure<graspPair_MPZ > (ListStructure<graspPair_MPZ>::ORDEM_CRESCENTE);
        node_list_struct<graspPair_MPZ> * gpnumber = GraspPairs->nextFromLastAcc();

        while ((gpnumber != NULL) && (gpnumber->element.id <= RclLimit)) {
            RCL->Add(gpnumber->element);
            gpnumber = GraspPairs->nextFromLastAcc();
        }
        int kesimo = rand() % RCL->getSize();
        graspPair_MPZ rclChosen = RCL->retrieve_K_esimo(kesimo)->element;
        partitionsSums[m] += rclChosen.number;
        partitions[m]->Add(number_element_mpz(rclChosen.number));
        numberSourceClone->RemoveObject(number_element_mpz(rclChosen.number));
        delete GraspPairs;
        delete RCL;
    }
    resultado = calculaResultado();
    delete numberSourceClone;
}

void NumberPartitionProblem_MPZ::GRASP(float alpha, int iter) {
    srand(time(NULL));
    graspConstruction(alpha);
    mpz_class melhorResultado = resultado;
    for (int i = 0; i < iter; i++) {
        descida();
        if (resultado < melhorResultado) {
            cout << resultado << "---" << melhorResultado << endl;
            bestResultado = melhorResultado = resultado;
            cloneSolutionToBest();
            if ((bestResultado == 1) || (bestResultado == 0)) {
                break;
            }
        }
        graspConstruction(alpha);
        //cout<<i<<endl;
    }
}

void NumberPartitionProblem_MPZ::IteratedLocalSearch(int MaxIter, float alpha, int MaxPerLvl) {
    srand(time(NULL));
    graspConstruction(alpha);
    descida();
    cloneSolutionToBest();
    //cout<<checkBestSolution()<<endl;
    bestResultado = resultado;
    int iter = 0;
    while (iter < MaxIter) {
        iter++;
        for (int i = 0; i < maxPertubations; i++) {
            for (int j = 0; j < MaxPerLvl; j++) {
                MakePertubation(i);
                descida();
                // cout<<resultado<<" "<<calculaResultado()<<" "<<"Best res: "<<checkSolution()<<endl;
                if (resultado < bestResultado) {
                    cloneSolutionToBest();
                    cout << "Iter: " << iter << " Nivel Pert: " << i << " Sol. Atual: " << resultado << " Melhor Sol.: " << bestResultado << endl;
                    //     cout<<"Best res: "<<checkBestSolution()<<endl;
                    bestResultado = resultado;
                    i = 0;
                    j = 0;
                    if ((bestResultado == 1) || (bestResultado == 0)) {
                        return;
                    }
                } else {
                    cloneSolutionFromBest();
                    //    cout<<"Best res: "<<checkBestSolution()<<endl;
                }

            }
        }
    }
}

void NumberPartitionProblem_MPZ::MakePertubation(int lvl) {
    for (int i = 0; i < pertubations[lvl].trocas; i++) {
        int PartOrig = rand() % nroParticoes;
        int PartDest;
        do {
            PartDest = rand() % nroParticoes;
        } while (PartDest == PartOrig);
        //printf("%x\n",partitions[PartOrig]->retrieve_K_esimo(rand()%partitions[PartOrig]->getSize()));
        node_list_struct<number_element_mpz> * numberOrigin = partitions[PartOrig]->retrieve_K_esimo(rand() % partitions[PartOrig]->getSize());
        node_list_struct<number_element_mpz> * numberDest = partitions[PartDest]->retrieve_K_esimo(rand() % partitions[PartDest]->getSize());
        //cout<<calculaResultado()<<" "<<checkSolution()<<endl;
        partitionsSums[PartOrig] = partitionsSums[PartOrig] - numberOrigin->element.id + numberDest->element.id;
        partitionsSums[PartDest] = partitionsSums[PartDest] - numberDest->element.id + numberOrigin->element.id;


        partitions[PartOrig]->Add(partitions[PartDest]->RemoveObject(numberDest));
        partitions[PartDest]->Add(partitions[PartOrig]->RemoveObject(numberOrigin));
        //        cout<<calculaResultado()<<" "<<checkSolution()<<endl;
        //        if(calculaResultado()!=checkSolution()){
        //            cout<<endl;
        //        }
    }
    for (int i = 0; i < pertubations[lvl].realoc; i++) {

        int PartOrig = rand() % nroParticoes;
        int PartDest;
        do {
            PartDest = rand() % nroParticoes;
        } while (PartDest == PartOrig);
        number_element_mpz numberOrigin = partitions[PartOrig]->retrieve_K_esimo(rand() % partitions[PartOrig]->getSize())->element;
        partitionsSums[PartOrig] = partitionsSums[PartOrig] - numberOrigin.id;
        partitionsSums[PartDest] = partitionsSums[PartDest] + numberOrigin.id;
        partitions[PartOrig]->RemoveObject(numberOrigin);
        partitions[PartDest]->Add(numberOrigin);
    }

    resultado = calculaResultado();
}

void NumberPartitionProblem_MPZ::constructPertubations() {
    for (int i = 0; i < maxPertubations; i++) {
        pertubations[i].trocas = i + 2;
    }
    int k = 0;
    for (int j = 0; j < maxPertubations; j++) {
        pertubations[j].realoc = k;
        k = ((j + 1) % 3 == 0) ? k + 1 : k;
    }
}

void NumberPartitionProblem_MPZ::cloneSolutionToBest() {
    for (int i = 0; i < nroParticoes; i++) {
        if (bestPartitions[i] != NULL)
            delete bestPartitions[i];
    }
    for (int i = 0; i < nroParticoes; i++) {
        bestPartitions[i] = partitions[i]->clone();
    }
}

void NumberPartitionProblem_MPZ::getListFromBkp(BookKeeping_mpz* b, ListStructure<number_element_mpz>*ret) {
    if (b->List == NULL) {
        number_element_mpz a(b->id);
        ret->Add(a);
    } else {
        for (int j = 0; j < b->nElem; j++) {
            getListFromBkp(b->List[j], ret);
        }
    }
}

void NumberPartitionProblem_MPZ::cloneSolutionToBest(ListOfSums_mpz *los) {
    for (int i = 0; i < nroParticoes; i++) {
        if (bestPartitions[i] != NULL)
            bestPartitions[i]->ClearList();
    }
    node_list_struct<BookKeeping_mpz*>*bkp;
    int j = 0;
    while ((bkp = los->List->nextFromLastAcc()) != NULL) {
        getListFromBkp(bkp->element, bestPartitions[j]);
        j++;
    }
    cloneSolutionFromBest();
    mpz_class res(calculaResultado() + 1);
    cout << log2_temp(res) << endl;
}

void NumberPartitionProblem_MPZ::getListFromBkp(bkp_bfs* b, ListStructure<number_element_mpz>*ret) {
    if (b->List == NULL) {
        number_element_mpz a(b->id);
        ret->Add(a);
    } else {
        for (int j = 0; j < b->nElem; j++) {
            getListFromBkp(b->List[j], ret);
        }
    }
}

void NumberPartitionProblem_MPZ::cloneSolutionToBest(los_bfs *los) {
    for (int i = 0; i < nroParticoes; i++) {
        if (bestPartitions[i] != NULL)
            bestPartitions[i]->ClearList();
    }
    node_list_struct<bkp_bfs*>*bkp;
    int j = 0;
    while ((bkp = los->List->nextFromLastAcc()) != NULL) {
        getListFromBkp(bkp->element, bestPartitions[j]);
        j++;
    }
    cloneSolutionFromBest();
    cout << log2_temp(calculaResultado() + 1) << endl;
}

int NumberPartitionProblem_MPZ::getQuantidade() const {
    return quantidade;
}

mpz_class NumberPartitionProblem_MPZ::getMedia() const {
    return media;
}

void NumberPartitionProblem_MPZ::cloneSolutionFromBest() {
    for (int i = 0; i < nroParticoes; i++) {
        delete partitions[i];
    }
    for (int i = 0; i < nroParticoes; i++) {
        partitionsSums[i] = 0;
        partitions[i] = bestPartitions[i]->clone();
    }
    for (int i = 0; i < nroParticoes; i++) {
        node_list_struct<number_element_mpz> * number = partitions[i]->nextFromLastAcc();
        while (number != NULL) {
            partitionsSums[i] += number->element.id;
            number = partitions[i]->nextFromLastAcc();
        }
    }
}


