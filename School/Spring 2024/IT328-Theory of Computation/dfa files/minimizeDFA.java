import java.util.ArrayList;

public class minimizeDFA {
    public static DFA minimize(DFA old){
        int numStates = old.numStates;
        boolean isComplete = false;
        char[] sigma = old.sigma;
        ArrayList<Boolean> accepting = old.getAccepting();
        int[][] transitions = old.getTrans();
        int[][] distTable = new int[numStates][numStates];
        int curTransState;
        int secTransState;
        for(int i = 0; i < distTable.length; i++){ // Step 1
            for(int j = 0; j < distTable[i].length; j++){
                distTable[i][j] = 0;
            }
        }
        
        for(int i = 0; i < distTable.length; i++){ // Step 2
            for(int j = i + 1; j < distTable[i].length; j++){
                if(accepting.get(i) != accepting.get(j)){
                    distTable[i][j] = 1;
                    distTable[j][i] = 1;
                }
            }
        }

        while(!isComplete){ // Step 3
            isComplete = true;
            for(int i = 0; i < distTable.length; i++){
                for(int j = i + 1; j < distTable[i].length; j++){
                    if(distTable[i][j] == 0){
                        for(int k = 0; k < sigma.length; k++){
                            curTransState = transitions[i][k];
                            secTransState = transitions[j][k];
                            if(distTable[i][curTransState] != distTable[j][secTransState]){
                                isComplete = false;
                                distTable[i][j] = 1;
                                distTable[j][i] = 1;
                            }
                        }
                    }
                }
            }
        }
        // //Distinguishables gotten
        // for(int i = 0; i < distTable.length; i++){
        //     for(int j = 0; j < distTable[i].length; j++){
        //         System.out.print(distTable[i][j] + " ");
        //     }
        //     System.out.println();
        // }

        // System.out.println("Trans: ");
        // for(int i = 0; i < transitions.length; i++){
        //     System.out.print(i + ": ");
        //     for(int j = 0; j < transitions[i].length; j++){
        //         System.out.print(transitions[i][j] + " ");
        //     }
        //     System.out.println();
        // }
        
        //Combining States
        ArrayList<ArrayList<Integer>> combineStates = new ArrayList<>();
        ArrayList<Integer> tempList = new ArrayList<>();
        ArrayList<Integer> skips = new ArrayList<>();

        for(int i = 0; i < distTable.length; i++){
            tempList.clear();
            tempList.add(i);
            if(!skips.contains(i)){
                for(int j = i + 1; j < distTable[i].length; j++){
                    if(distTable[i][j] == 0){
                        tempList.add(j);
                        skips.add(j);
                    }
                }
                combineStates.add(new ArrayList<>(tempList));
            }
        }

        ArrayList<Boolean> newAccepting = new ArrayList<>();
        ArrayList<ArrayList<Integer>> newTransition = new ArrayList<>();

        for(ArrayList<Integer> state : combineStates){
            newAccepting.add(accepting.get(state.get(0)));
        }

        boolean isFound;

        for(int i = 0; i < combineStates.size(); i++){
            ArrayList<Integer> curTrans = new ArrayList<>();
            for(int j = 0; j < transitions[i].length; j++){ //Gets each transition from the table
                isFound = false;
                for(int k = 0; k < combineStates.size(); k++){
                    for(int l = 0; l < combineStates.get(k).size(); l++){ // Finds its new state
                        if(transitions[i][j] == combineStates.get(k).get(l)){
                            isFound = true;
                            curTrans.add(k);
                            break;
                        }
                    }
                    if(isFound){
                        break;
                    }
                }
            }
            newTransition.add(curTrans);
        }
        
        // for(int i = 0; i < combineStates.size(); i++){
        //     System.out.print(i + ": ");
        //     for(int j = 0; j < combineStates.get(i).size(); j++){
        //         System.out.print(combineStates.get(i).get(j) + " ");
        //     }
        //     System.out.println();
        // }

        // for(int i = 0; i < newTransition.size(); i++){
        //     System.out.print(i + ": ");
        //     for(int j = 0; j < newTransition.get(i).size(); j++){
        //         System.out.print(newTransition.get(i).get(j) + " ");
        //     }
        //     System.out.println();
        // }

        return new DFA(combineStates, newTransition, sigma, newAccepting); // Sigma 
    }
    
}
