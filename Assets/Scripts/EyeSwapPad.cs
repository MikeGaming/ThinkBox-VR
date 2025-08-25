using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EyeSwapPad : MonoBehaviour
{

    [SerializeField] GameObject[] buttonPanels;

    private void Start()
    {
    }

    public void SwapPads(int index)
    {
        for (int i = 0; i < buttonPanels.Length; i++)
        {
            if (i == index)
            {
                buttonPanels[i].SetActive(true);
            }
            else
            {
                buttonPanels[i].SetActive(false);
            }
        }
    }

}
