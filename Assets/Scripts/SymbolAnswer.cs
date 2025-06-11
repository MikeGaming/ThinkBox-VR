using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;

public class SymbolAnswer : MonoBehaviour
{
    int[] symbolOrder = new int[4] { 5, 5, 5, 5 };
    List<int> symbolNumbers = new List<int> { 1, 2, 3, 4 };
    List<int> symbolOrderNumbers = Enumerable.Range(1, 4).ToList();
    [SerializeField] MessageController messageListener;
    [SerializeField] GameObject[] symbols;
    [HideInInspector] public string lastMessage_symbol;
    [HideInInspector] public string solved;
    [SerializeField] Text[] symbolAnswerTexts = new Text[4];
    bool triggered;
    int n = 0;
    int r;

    void Start()
    {
        for (int i = 0; i < symbolOrder.Length; i++)
        {
            r = symbolNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolOrder[i] = r;
            if (r == 1)
            {
                symbolAnswerTexts[i].text = "◆";
            }
            else if (r == 2)
            {
                symbolAnswerTexts[i].text = "■";
            }
            else if (r == 3)
            {
                symbolAnswerTexts[i].text = "●";
            }
            else if (r == 4)
            {
                symbolAnswerTexts[i].text = "▲";
            }
            symbolNumbers.Remove(r);
            print(r);
        }
        StartCoroutine(SendText("#" + symbolOrder[0] + symbolOrder[1] + symbolOrder[2] + symbolOrder[3]));
    }
    IEnumerator SendText(string text)
    {
        yield return new WaitForSeconds(1f);
        messageListener.SendTextData(text);
        StopAllCoroutines();
    }
    void Update()
    {
        if (lastMessage_symbol == "s" && n < 2 && symbolOrderNumbers.Count != 0)
        {
            r = symbolOrderNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolAnswerTexts[r - 1].gameObject.SetActive(true);
            symbolOrderNumbers.Remove(r);
            r = symbolOrderNumbers.OrderBy(bn => Guid.NewGuid()).FirstOrDefault();
            symbolAnswerTexts[r - 1].gameObject.SetActive(true);
            symbolOrderNumbers.Remove(r);
            lastMessage_symbol = "";
            n++;
        }

        if (solved == "s")
        {
            symbols[0].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            symbols[1].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            symbols[2].GetComponent<MeshRenderer>().materials[0].color = Color.green;
            symbols[3].GetComponent<Image>().color = Color.green;
        }
    }
}
