using UnityEngine;

namespace AKB.Entities.Interactions
{
    public class CharmedStatusEffect : StatusEffect
    {
        [SerializeField] float moveSpeed;

        float timeCache;

        ICharmable charmable;
        Transform shotFromEntity;

        Vector3 directionToMove;

        public override void OnEnable()
        {
            base.AttachToEntity();

            timeCache = activeTime;

            charmable = transform.root.gameObject.GetComponent<ICharmable>();

            if (charmable != null)
            {
                if (charmable.IsAlreadyCharmed())
                {
                    base.DestroyEffect();
                }
                else
                {
                    shotFromEntity = charmable.GetInflictedFromDirection();

                    charmable.DeactivateEntityControls();

                    ApplyVFXToEntity(GetAttachedEntity());

                    isActive = true;
                }
            }
        }

        public override void Update()
        {
            if (isActive)
            {
                timeCache -= Time.deltaTime;
                if (timeCache <= 0)
                {
                    StopEffect();
                }
                else
                {
                    EffectBehaviour();
                }
            }
        }

        public override void EffectBehaviour()
        {
            directionToMove = transform.root.position - shotFromEntity.position;

            transform.root.position -= directionToMove * moveSpeed * Time.deltaTime;

            Debug.Log("Moving");
        }

        public override void StopEffect()
        {
            base.StopEffect();

            charmable.ActivateEntityControls();

            base.DestroyEffect();
        }

        public override void OnDisable()
        {
            charmable = null;
            attachedEntity = null;
            shotFromEntity = null;

            isActive = false;
        }
    }
}
