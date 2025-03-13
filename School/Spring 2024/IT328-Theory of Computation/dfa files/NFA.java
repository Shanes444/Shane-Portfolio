import java.util.ArrayList;
import java.util.LinkedHashSet;

public class NFA {

    int q;
    int initial;
    char[] sigma;
    State[] states;

    

    public NFA(int q, int initial, char[] sigma, boolean[][][] pathlist, boolean[] isAccepting){
        this.q = q;
        this.initial = initial;
        this.sigma = sigma;
        states = new State[q];
        for(int i = 0; i < q; i++){
            states[i] = new State(pathlist[i], i, isAccepting[i]);
        }
    }

    // public String toString(){

    // }

    public ArrayList<Integer> lambdaClosure(int state){
        ArrayList<Integer> lamdaClos = new ArrayList<>();
        lamdaClos.add(state);
        states[state].getClosure(lamdaClos);
        return lamdaClos;
    }

    public ArrayList<Integer> whereCanGo(ArrayList<Integer> statesToCheck, char alpha){ 
        int sigInd = -1;
        LinkedHashSet<Integer> allStates = new LinkedHashSet<>(); //This is to remove duplicates
        for(int i = 0; i < sigma.length; i++){
            if(sigma[i] == alpha){
                sigInd = i;
                break;
            }
        }
        for(Integer i : statesToCheck){
            allStates.addAll(states[i].getStates(sigInd));
        }
        ArrayList<Integer> closureStates = new ArrayList<>();
        boolean addNew = true;
        boolean tempNew = false;
        while(addNew){
            addNew = false;
            for(Integer i : allStates){
                closureStates.add(i);
                tempNew = states[i].getClosure(closureStates);
                if(tempNew){
                    addNew = tempNew;
                }
            }
            allStates.addAll(closureStates);
        }
        

        return new ArrayList<Integer>(allStates);
    }

    public boolean accept(ArrayList<Integer> stateList){
        for(Integer curState : stateList){
            if(states[curState].isAccepting){
                return true;
            }
        }
        return false;
    }

    class State{
        boolean[][] paths; //[i][j] i - sigma j - to another state
        boolean isAccepting;
        int ownStateNum;

        public State(boolean[][] p, int q, boolean Accept){
            paths = p;
            isAccepting = Accept;
            ownStateNum = q;
        }

        public boolean getClosure(ArrayList<Integer> lamdaClos){
            int lamdaInd = paths.length - 1;
            boolean isNew = false;
            for(int i = 0; i < paths[lamdaInd].length; i++){
                if(paths[lamdaInd][i] && i != ownStateNum && !lamdaClos.contains(i)){
                    lamdaClos.add(i);
                    isNew = true;
                }
            }
            return isNew;
        }

        public ArrayList<Integer> getStates(int sigmaInd){
            ArrayList<Integer> alphaStates = new ArrayList<>();
            for(int i = 0; i < paths[sigmaInd].length; i++){
                if(paths[sigmaInd][i]){
                    alphaStates.add(i);
                }
            }
            return alphaStates;
        }
    }
}
