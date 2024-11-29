using UnityEngine;

public class LEDARRAY : MonoBehaviour
{

    [SerializeField] MessageController messageListener;

    private void Start()
    {
        messageListener.SendTextData("");
    }
}
